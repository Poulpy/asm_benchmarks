//
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

//
#include "rdtsc.h"

//
#include "stats.h"

//
#define ALIGN 64

//A cacheline is 64 bytes 
#define CACHELINE_SIZE 64

//
#define MAX_SAMPLES 33

//
typedef unsigned long long u64;

//
u64 randxy(u64 x, u64 y)
{ return x + (rand() % (y - x)); }

//
void init(void **restrict a, u64 n)
{
  for (u64 i = 0; i < n; i++)
    a[i] = &a[i]; //printf("%p %p\n", tmp, a[i]);
}

//
void shuffle(void **restrict a, u64 n)
{
  //
  u64 i = 0;
  u64 ii = 0;
  u64 nn = n;
  
  //
  while (i < nn)
    {
      //Pick a random position between 0 and nn - 8
      ii = randxy(0, nn - 8);

      //Make sure ii is dividable by 8
      ii -= (ii & 7);
  
      //Swap the ii pointer values with last elements
      for (u64 j = 0; j < CACHELINE_SIZE / sizeof(void *); j++)
	{
	  void *tmp = a[j + nn - 8];

	  a[j + nn - 8] = a[j + ii];
	  a[j + ii] = tmp;
	}
      
      //
      nn -= 8;
      
      //
      i += 8;
    }
}

//
void walk(void **restrict a, u64 n, u64 r)
{
  //n / 8 ==> number of groups of 8 elements (cacheline)
  u64 nn = n / sizeof(void *);
  
  //
  const void *p = a[0];
  
  //
  for (u64 i = 0; i < r; i++)
    {
      //index = a[index];
      __asm__ volatile (
			"xor %%rcx, %%rcx;\n"
			"mov (%[_p_]), %%rax;\n"
			
			"1:;\n"

			//32B load (1/2 a cacheline)
			"vmovdqa (%%rax), %%ymm0;\n"
			"vmovq %%xmm0, %%rax;\n"
			
			"inc %%rcx;\n"
			"cmp %[_n_], %%rcx;\n"
			"jl 1b;\n"
			
			: //output
			: //input
			  [_p_] "r" (p),
			  [_n_] "r" (nn)
			: //clobber
			  "cc", "memory",
			  "rax", "rcx",
			  "xmm0",
			  "ymm0"
			);      
    }
}

//
double measure_time(void **a,
		    unsigned long long s,
		    unsigned long long r)
{
  //
  double elapsed = 0.0;
  struct timespec after, before;
  
  //
  do
    {
      //
      clock_gettime(CLOCK_MONOTONIC_RAW, &before);
      
      //
      walk(a, s, r);

      //
      clock_gettime(CLOCK_MONOTONIC_RAW, &after);

      //
      elapsed = (double)(after.tv_nsec - before.tv_nsec) / (double)r;
    }
  while (elapsed <= 0.0);

  //
  return elapsed;
}

//
double measure_cycles(void **a,
		      unsigned long long s,
		      unsigned long long r)
{
  //
  double elapsed = 0.0;
  unsigned long long after = 0.0, before = 0.0;
  
  //
  before = rdtsc();
  
  //
  walk(a, s, r);
  
  //
  after = rdtsc();
  
  //
  elapsed = (double)(after - before) / (double)r;
  
  //
  return elapsed;
}

//
int main(int argc, char **argv)
{
  //
  srand(getpid());

  //Size in bytes
  //Number of kernel runs
  if (argc < 3)
    return printf("Usage: %s [s] [r]\n", argv[0]), 1;
  
  //
  u64 s = atoll(argv[1]);
  u64 r = atoll(argv[2]);

  //
  u64 n = s / sizeof(void *);
  n -= (n & 8);

  //
  double s_kib = (double)s / 1024.0;
  double s_mib = s_kib / 1024.0;
  double s_gib = s_mib / 1024.0;

  //
  double times[MAX_SAMPLES];
  double cycles[MAX_SAMPLES];
  
  //
  void **a = aligned_alloc(ALIGN, n * sizeof(void *));

  //
  fprintf(stderr, "pc; %.4lf KiB, %.4lf MiB, %.4lf GiB; %llu 64-bit elements/iterations\n",
	  s_kib,
	  s_mib,
	  s_gib,
	  n);
  
  //
  init(a, n);
  
  //
  shuffle(a, n);

  //Run time
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    times[i] = measure_time(a, s, r);
  
  //
  printf("(s, ns, GiB/s):\n");
  
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    printf("%3u, %.3lf, %.3lf, %.3lf\n",
	   i,
	   times[i] / 1e9,    //Convert ns to s
	   times[i],
	   s_gib / (times[i] / 1e9));
  
  print_stats(times, MAX_SAMPLES);
  
  //Run cycles
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    cycles[i] = measure_cycles(a, s, r);
  
  //
  printf("\n\n(cycles, CPIt, CPI):\n");
  
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    printf("%3u, %.3lf, %.3lf, %.3lf\n",
	   i,
	   cycles[i],
	   cycles[i] / n,
	   cycles[i] / (n * 5));

  print_stats(cycles, MAX_SAMPLES);
  
  //
  free(a);
  
  return 0;
}

//
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

//
#include "rdtsc.h"

//
#include "stats.h"

//
#define ALIGN 32

//A cacheline is 64 bytes 
#define CACHELINE_SIZE 64

//
#define MAX_SAMPLES 33

//
void init(double *restrict a, double c, unsigned long long n)
{
  for (unsigned long long i = 0; i < n; i++)
    a[i] = c;
}

//
double measure_time(void *restrict a,
		    void *restrict b,
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
      for (unsigned long long i = 0; i < r; i++)
	memcpy(a, b, s);
      
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
double measure_cycles(void *restrict a,
		      void *restrict b,
		      unsigned long long s,
		      unsigned long long r)
{
  //
  double elapsed = 0.0;
  unsigned long long after = 0.0, before = 0.0;
  
  //
  before = rdtsc();
  
  //
  for (unsigned long long i = 0; i < r; i++)
    memcpy(a, b, s);
  
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
  unsigned long long s = atoll(argv[1]);
  unsigned long long r = atoll(argv[2]);

  //
  unsigned long long n = s / sizeof(void *);
  n -= (n & 8);

  //
  double s_kib = (double)s / 1024.0;
  double s_mib = s_kib / 1024.0;
  double s_gib = s_mib / 1024.0;

  //
  double times[MAX_SAMPLES];
  double cycles[MAX_SAMPLES];
  
  //
  void *restrict a = aligned_alloc(ALIGN, n * sizeof(double));
  void *restrict b = aligned_alloc(ALIGN, n * sizeof(double));

  //
  fprintf(stderr, "pc; %.4lf KiB, %.4lf MiB, %.4lf GiB; %llu 64-bit elements/iterations\n",
	  s_kib,
	  s_mib,
	  s_gib,
	  n);
  
  //
  init(a, 0.0, n);
  init(b, 1.0, n);
  
  //Run time
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    times[i] = measure_time(a, b, s, r);
  
  //
  printf("(s, ns, GiB/s):\n");
  
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    printf("%3u, %20.3lf, %20.3lf, %10.3lf\n",
	   i,
	   times[i] / 1e9,    //Convert ns to s
	   times[i],
	   s_gib / (times[i] / 1e9));
  
  print_stats(times, MAX_SAMPLES);

  //
  init(a, 0.0, n);
  init(b, 1.0, n);

  //Run cycles
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    cycles[i] = measure_cycles(a, b, s, r);
  
  //
  printf("\n\n(cycles, CPIt, CPI):\n");
  
  for (unsigned i = 0; i < MAX_SAMPLES; i++)
    printf("%3u, %20.3lf, %20.3lf, %20.3lf\n",
	   i,
	   cycles[i],
	   cycles[i] / n,
	   cycles[i] / (n * 5));

  print_stats(cycles, MAX_SAMPLES);
  
  //
  free(a);
  free(b);

  //
  return 0;
}

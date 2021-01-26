//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
#include "kern.h"

//
#include "stats.h"

//
void _init_(double *restrict a, double c, unsigned long long n)
{
  for (unsigned long long i = 0; i < n; i++)
    a[i] = c;
}

//
run_t *create_run(const unsigned nb_arrays,
		  const unsigned long long s,
		  const unsigned long long r,
		  const unsigned ALIGN,
		  const double *ops,
		  const char **fctnames,
		  const void (*fctptrs[])(run_t *),
		  const unsigned nb_samples)
{
  //
  run_t *run = malloc(sizeof(run_t));
  
  //
  if (run)
    {
      //
      run->a = NULL;

      //
      if (nb_arrays)
	{
	  //
	  run->a = malloc(sizeof(double *) * nb_arrays); 

	  if (!run->a)
	    return printf("Error: cannot allocate memory for arrays\n"), NULL;
	  
	  //
	  run->nb_arrays = nb_arrays;
	}
      else
	return NULL;
      
      //
      if (s)
	run->s = s;
      else
	return printf("Error: size cannot be zero\n"), NULL;

      //
      if (r)
	run->r = r;
      else
	return printf("Error: number of runs cannot be zero\n"), NULL;
      
      //
      switch (ALIGN)
	{
	  //
	case ALIGN_SSE:
	case ALIGN_AVX:
	case ALIGN_AVX512:

	  run->ALIGN = ALIGN;
	  break;

	  //
	default:
	  return printf("Error: value '%u' is not allowed for memory alignment\n", ALIGN), NULL;
	}

      //
      if (ops)
	run->ops = ops;
      else
	return NULL;
      
      //
      if (fctnames)
	run->fctnames = fctnames;
      else
	return NULL;
      
      //
      if (fctptrs)
	run->fctptrs = fctptrs;
      else
	return NULL;
      
      //
      run->nb_samples = nb_samples;
      
      //
      run->samples = malloc(sizeof(double) * nb_samples);

      //
      if (!run->samples)
	return printf("Error: cannot allocate memory for samples\n"), NULL;

      //
      run->f = 0;
      
      //
      return run;
    }
  else
    return printf("Error: cannot create run\n"), NULL;
}

//
void dump_run(const char *fctname, run_t *run)
{
  //
  if (run)
    {
      double s_kib = (double)run->s / 1024.0;
      double s_mib = s_kib / 1024.0;
      double s_gib = s_mib / 1024.0;
       
      fprintf(stdout, "%20s; %llu; %.3lf, %.3lf, %.3lf; %.3lf; %.3lf; %.3lf; %.3lf; %7.3lf %%; %.3lf; %.3lf\n",
	      fctname,
	      run->f,
	      s_kib,
	      s_mib,
	      s_gib,
	      run->min,
	      run->max,
	      run->mean,
	      run->median,
	      run->stddevp,
	      run->gibps,
	      run->flops);
    }
}

//
void stats_run(run_t *run)
{
  //
  if (run)
    {
      //
      sort(run->samples, run->nb_samples);
      
      //
      run->min    = run->samples[0];
      run->max    = run->samples[run->nb_samples - 1];
      run->mean   = mean(run->samples, run->nb_samples);
      run->median = (run->samples[run->nb_samples >> 1] + run->samples[(run->nb_samples >> 1) + 1]) / 2.0;
      
      //
      run->stddev = stddev(run->samples, run->nb_samples);
      run->stddevp = (run->stddev * 100.0) / run->mean;
      
      //Compute total used memory size in bytes
      unsigned long long s = run->s * run->nb_arrays;
      
      //Convert size to GiB
      double s_gib = (double)s / (1024.0 * 1024.0 * 1024.0);
      
      //Convert elapsed mean time from nano-seconds to seconds
      double elapsed_s = run->mean / 1000000000.0;
      
      //
      run->gibps = s_gib / elapsed_s; 
    }
}

//
void do_run(run_t *run)
{
  //
  unsigned i = 0;
  
  //
  double elapsed = 0.0;
  struct timespec after, before;

  //
  void (*kernel)(run_t *) = NULL;
  
  //Go through each kernel
  while (run->fctptrs[i])
    {
      //
      kernel = run->fctptrs[i];
      
      //Collect samples
      for (unsigned long long j = 0; j < run->nb_samples; j++)
	{
	  //Allocate memory
	  for (unsigned jj = 0; jj < run->nb_arrays; jj++)
	    {
	      run->a[jj] = aligned_alloc(run->ALIGN, run->s);
	      _init_(run->a[jj], 1.0, run->s / sizeof(double));
	    }
	  
	  //Re-run if wrap around
	  do
	    { 
	      //
	      clock_gettime(CLOCK_MONOTONIC_RAW, &before);
	      
	      //
	      kernel(run);
	      
	      //
	      clock_gettime(CLOCK_MONOTONIC_RAW, &after);
	      
	      //
	      elapsed = (double)(after.tv_nsec - before.tv_nsec) / run->r;
	      
	      //Count fails
	      run->f += (elapsed <= 0.0);
	    }
	  while (elapsed <= 0.0);
	  
	  //
	  run->samples[j] = elapsed; 
	  
	  //Free memory
	  for (unsigned jj = 0; jj < run->nb_arrays; jj++)
	    free(run->a[jj]);
	}

      //
      stats_run(run);

      //
      run->flops = (run->ops[i] * (run->s / sizeof(double))) / run->mean;

      //
      dump_run(run->fctnames[i], run);
      
      //
      i++;
    }
}

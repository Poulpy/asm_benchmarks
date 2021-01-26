#ifndef RUN_H
#define RUN_H

//
typedef struct run_s run_t;

//
struct run_s {

  //Array pointers
  double **a;
  unsigned nb_arrays;
  
  //Memory size
  unsigned long long s;

  //Number of kernel runs
  unsigned long long r;

  //
  unsigned ALIGN;
  
  //
  const double *ops;
  const char **fctnames;
  const void (**fctptrs)(run_t *);

  //
  double *samples;
  unsigned nb_samples;
  
  //
  double min;
  double max;
  double mean;
  double median;

  //
  double stddev;
  double stddevp;

  //
  double gibps;

  //
  double flops;

  //
  unsigned long long f;
};

//
run_t *create_run(const unsigned nb_arrays,
		  const unsigned long long s,
		  const unsigned long long r,
		  const unsigned ALIGN,
		  const double *ops,
		  const char **fctnames,
		  const void (*fctptrs[])(run_t *),
		  const unsigned nb_samples);

//
void do_run(run_t *run);

//
void dump_run(const char *fctname, run_t *run);

//
void stats_run(run_t *run);

//
#endif

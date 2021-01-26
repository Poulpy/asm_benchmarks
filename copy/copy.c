//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//
#include "kern.h"

//
#include "run.h"


//s: memory size in bytes
//r: number of kernel repetitions
int main(int argc, char **argv)
{
  //
  if (argc < 3)
    return printf("%s [s] [r]\n", argv[0]), 1;

  //
  unsigned long long s = atoll(argv[1]);
  unsigned long long r = atoll(argv[2]);
  
  //Run SSE
  run_t *run_SSE = create_run(2, s, r, ALIGN_SSE, copy_SSE_fctnames, copy_SSE_fctptrs, 33);
  do_run(run_SSE);
  
  //Run AVX
#ifdef AVX
  run_t *run_AVX = create_run(2, s, r, ALIGN_AVX, copy_AVX_fctnames, copy_AVX_fctptrs, 33);
  do_run(run_AVX);
#endif

#ifdef AVX512

  //Run AVX
  run_t *run_AVX512 = create_run(2, s, r, ALIGN_AVX512, copy_AVX512_fctnames, copy_AVX512_fctptrs, 33);
  do_run(run_AVX512);
  
#endif
  
  //
  return 0;
}

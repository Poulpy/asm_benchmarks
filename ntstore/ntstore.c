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
  run_t *run_SSE = create_run(1, s, r, ALIGN_SSE, ntstore_SSE_fctnames, ntstore_SSE_fctptrs, 33);
  do_run(run_SSE);
  
  //Run AVX
  run_t *run_AVX = create_run(1, s, r, ALIGN_AVX, ntstore_AVX_fctnames, ntstore_AVX_fctptrs, 33);
  do_run(run_AVX);

#ifdef AVX512

  //Run AVX
  run_t *run_AVX512 = create_run(1, s, r, ALIGN_AVX512, ntstore_AVX512_fctnames, ntstore_AVX512_fctptrs, 33);
  do_run(run_AVX512);
  
#endif
  
  //
  return 0;
}

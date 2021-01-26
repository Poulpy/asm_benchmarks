#ifndef KERN_H
#define KERN_H

//For NULL
#include <stdlib.h>

#include "run.h"

//Memory alignments 
#define ALIGN_SSE    16
#define ALIGN_AVX    32
#define ALIGN_AVX512 64

//
void ntstore_SSE_16B(run_t *run);
void ntstore_SSE_32B(run_t *run);
void ntstore_SSE_64B(run_t *run);
void ntstore_SSE_128B(run_t *run);

//
void ntstore_AVX_32B(run_t *run);
void ntstore_AVX_64B(run_t *run);
void ntstore_AVX_128B(run_t *run);
void ntstore_AVX_256B(run_t *run);

//
void ntstore_AVX512_64B(run_t *run);
void ntstore_AVX512_128B(run_t *run);
void ntstore_AVX512_256B(run_t *run);
void ntstore_AVX512_512B(run_t *run);

//Sizes of memory accesses per iteration for SSE kernels
static const unsigned long long ntstore_SSE_sizes[] = { 16, 32, 64, 128 };

//Sizes of memory accesses per iteration for AVX kernels
static const unsigned long long ntstore_AVX_sizes[] = { 32, 64, 128, 256 };

//Sizes of memory accesses per iteration for AVX512  kernels
static const unsigned long long ntstore_AVX512_sizes[] = { 64, 128, 256, 512 };

//
static const void (*ntstore_SSE_fctptrs[])(run_t *) = {

  ntstore_SSE_16B,
  ntstore_SSE_32B,
  ntstore_SSE_64B,
  ntstore_SSE_128B,

  NULL };

//
static const char *ntstore_SSE_fctnames[] = { "ntstore_SSE_16B", "ntstore_SSE_32B", "ntstore_SSE_64B", "ntstore_SSE_128B", NULL };

//
static const void (*ntstore_AVX_fctptrs[])(run_t *) = {

  ntstore_AVX_32B,
  ntstore_AVX_64B,
  ntstore_AVX_128B,
  ntstore_AVX_256B,

  NULL };

//
static const char *ntstore_AVX_fctnames[] = { "ntstore_AVX_32B", "ntstore_AVX_64B", "ntstore_AVX_128B", "ntstore_AVX_256B", NULL };

//
static const void (*ntstore_AVX512_fctptrs[])(run_t *) = {

  ntstore_AVX512_64B,
  ntstore_AVX512_128B,
  ntstore_AVX512_256B,
  ntstore_AVX512_512B,

  NULL };

//
static const char *ntstore_AVX512_fctnames[] = { "ntstore_AVX512_64B", "ntstore_AVX512_128B", "ntstore_AVX512_256B", "ntstore_AVX512_512B", NULL };

#endif

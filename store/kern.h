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
void store_SSE_16B(run_t *run);
void store_SSE_32B(run_t *run);
void store_SSE_64B(run_t *run);
void store_SSE_128B(run_t *run);

//
void store_AVX_32B(run_t *run);
void store_AVX_64B(run_t *run);
void store_AVX_128B(run_t *run);
void store_AVX_256B(run_t *run);

//
void store_AVX512_64B(run_t *run);
void store_AVX512_128B(run_t *run);
void store_AVX512_256B(run_t *run);
void store_AVX512_512B(run_t *run);

//Sizes of memory accesses per iteration for SSE kernels
static const unsigned long long store_SSE_sizes[] = { 16, 32, 64, 128 };

//Sizes of memory accesses per iteration for AVX kernels
static const unsigned long long store_AVX_sizes[] = { 32, 64, 128, 256 };

//Sizes of memory accesses per iteration for AVX512  kernels
static const unsigned long long store_AVX512_sizes[] = { 64, 128, 256, 512 };

//
static const void (*store_SSE_fctptrs[])(run_t *) = {

  store_SSE_16B,
  store_SSE_32B,
  store_SSE_64B,
  store_SSE_128B,

  NULL };

//
static const char *store_SSE_fctnames[] = { "store_SSE_16B", "store_SSE_32B", "store_SSE_64B", "store_SSE_128B", NULL };

//
static const void (*store_AVX_fctptrs[])(run_t *) = {

  store_AVX_32B,
  store_AVX_64B,
  store_AVX_128B,
  store_AVX_256B,

  NULL };

//
static const char *store_AVX_fctnames[] = { "store_AVX_32B", "store_AVX_64B", "store_AVX_128B", "store_AVX_256B", NULL };

//
static const void (*store_AVX512_fctptrs[])(run_t *) = {

  store_AVX512_64B,
  store_AVX512_128B,
  store_AVX512_256B,
  store_AVX512_512B,

  NULL };

//
static const char *store_AVX512_fctnames[] = { "store_AVX512_64B", "store_AVX512_128B", "store_AVX512_256B", "store_AVX512_512B", NULL };

#endif

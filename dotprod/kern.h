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
void dotprod_SSE_16B(run_t *run);
void dotprod_SSE_32B(run_t *run);
void dotprod_SSE_64B(run_t *run);

//
void dotprod_AVX_32B(run_t *run);
void dotprod_AVX_64B(run_t *run);
void dotprod_AVX_128B(run_t *run);
void dotprod_AVX_256B(run_t *run);

//
void dotprod_AVX512_64B(run_t *run);
void dotprod_AVX512_128B(run_t *run);
void dotprod_AVX512_256B(run_t *run);
void dotprod_AVX512_512B(run_t *run);

//Sizes of memory accesses per iteration for kernels
static const unsigned long long dotprod_SSE_sizes[]    = { 16, 32, 64 };
static const unsigned long long dotprod_AVX_sizes[]    = { 32, 64, 128, 256 };
static const unsigned long long dotprod_AVX512_sizes[] = { 64, 128, 256, 512 };

//Number of operations (for FLOPS)
static const double dotprod_SSE_ops[]    = { 2.0, 4.0, 8.0 };
static const double dotprod_AVX_ops[]    = { 2.0, 4.0, 8.0, 16.0 };
static const double dotprod_AVX512_ops[] = { 2.0, 4.0, 8.0, 16.0 };

//
static const char *dotprod_SSE_fctnames[]    = { "dotprod_SSE_16B", "dotprod_SSE_32B", "dotprod_SSE_64B", NULL };
static const char *dotprod_AVX_fctnames[]    = { "dotprod_AVX_32B", "dotprod_AVX_64B", "dotprod_AVX_128B", "dotprod_AVX_256B", NULL };
static const char *dotprod_AVX512_fctnames[] = { "dotprod_AVX512_64B", "dotprod_AVX512_128B", "dotprod_AVX512_256B", "dotprod_AVX512_512B", NULL };

//
static const void (*dotprod_SSE_fctptrs[])(run_t *) = {

  dotprod_SSE_16B,
  dotprod_SSE_32B,
  dotprod_SSE_64B,
  
  NULL };

//
static const void (*dotprod_AVX_fctptrs[])(run_t *) = {

  dotprod_AVX_32B,
  dotprod_AVX_64B,
  dotprod_AVX_128B,
  dotprod_AVX_256B,

  NULL };


//
static const void (*dotprod_AVX512_fctptrs[])(run_t *) = {

  dotprod_AVX512_64B,
  dotprod_AVX512_128B,
  dotprod_AVX512_256B,
  dotprod_AVX512_512B,

  NULL };

#endif

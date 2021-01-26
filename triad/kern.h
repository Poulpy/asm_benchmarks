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
void triad_SSE_16B(run_t *run);
void triad_SSE_32B(run_t *run);
void triad_SSE_64B(run_t *run);

//
void triad_AVX_32B(run_t *run);
void triad_AVX_64B(run_t *run);
void triad_AVX_128B(run_t *run);
void triad_AVX_256B(run_t *run);

//
void triad_AVX512_64B(run_t *run);
void triad_AVX512_128B(run_t *run);
void triad_AVX512_256B(run_t *run);
void triad_AVX512_512B(run_t *run);

//Sizes of memory accesses per iteration for kernels
static const unsigned long long triad_SSE_sizes[]    = { 16, 32, 64 };
static const unsigned long long triad_AVX_sizes[]    = { 32, 64, 128, 256 };
static const unsigned long long triad_AVX512_sizes[] = { 64, 128, 256, 512 };

//Number of operations (for FLOPS)
static const double triad_SSE_ops[]    = { 2.0, 4.0, 8.0 };
static const double triad_AVX_ops[]    = { 2.0, 4.0, 8.0, 16.0 };
static const double triad_AVX512_ops[] = { 2.0, 4.0, 8.0, 16.0 };

//
static const char *triad_SSE_fctnames[]    = { "triad_SSE_16B", "triad_SSE_32B", "triad_SSE_64B", NULL };
static const char *triad_AVX_fctnames[]    = { "triad_AVX_32B", "triad_AVX_64B", "triad_AVX_128B", "triad_AVX_256B", NULL };
static const char *triad_AVX512_fctnames[] = { "triad_AVX512_64B", "triad_AVX512_128B", "triad_AVX512_256B", "triad_AVX512_512B", NULL };

//
static const void (*triad_SSE_fctptrs[])(run_t *) = {

  triad_SSE_16B,
  triad_SSE_32B,
  triad_SSE_64B,
  
  NULL };

//
static const void (*triad_AVX_fctptrs[])(run_t *) = {

  triad_AVX_32B,
  triad_AVX_64B,
  triad_AVX_128B,
  triad_AVX_256B,

  NULL };


//
static const void (*triad_AVX512_fctptrs[])(run_t *) = {

  triad_AVX512_64B,
  triad_AVX512_128B,
  triad_AVX512_256B,
  triad_AVX512_512B,

  NULL };

#endif

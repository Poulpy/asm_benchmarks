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
void reduc_SSE_16B(run_t *run);
void reduc_SSE_32B(run_t *run);
void reduc_SSE_64B(run_t *run);
void reduc_SSE_128B(run_t *run);

//
void reduc_AVX_32B(run_t *run);
void reduc_AVX_64B(run_t *run);
void reduc_AVX_128B(run_t *run);
void reduc_AVX_256B(run_t *run);

//
void reduc_AVX512_64B(run_t *run);
void reduc_AVX512_128B(run_t *run);
void reduc_AVX512_256B(run_t *run);
void reduc_AVX512_512B(run_t *run);

//Sizes of memory accesses per iteration for kernels
static const unsigned long long reduc_SSE_sizes[]    = { 16, 32, 64, 128 };
static const unsigned long long reduc_AVX_sizes[]    = { 32, 64, 128, 256 };
static const unsigned long long reduc_AVX512_sizes[] = { 64, 128, 256, 512 };

//Number of operations (for FLOPS)
static const double reduc_SSE_ops[]    = { 1.0, 2.0, 4.0, 8.0 };
static const double reduc_AVX_ops[]    = { 1.0, 2.0, 4.0, 8.0 };
static const double reduc_AVX512_ops[] = { 1.0, 2.0, 4.0, 8.0 };

//
static const char *reduc_SSE_fctnames[]    = { "reduc_SSE_16B", "reduc_SSE_32B", "reduc_SSE_64B", "reduc_SSE_128B", NULL };
static const char *reduc_AVX_fctnames[]    = { "reduc_AVX_32B", "reduc_AVX_64B", "reduc_AVX_128B", "reduc_AVX_256B", NULL };
static const char *reduc_AVX512_fctnames[] = { "reduc_AVX512_64B", "reduc_AVX512_128B", "reduc_AVX512_256B", "reduc_AVX512_512B", NULL };

//
static const void (*reduc_SSE_fctptrs[])(run_t *) = {

  reduc_SSE_16B,
  reduc_SSE_32B,
  reduc_SSE_64B,
  reduc_SSE_128B,

  NULL };

//
static const void (*reduc_AVX_fctptrs[])(run_t *) = {

  reduc_AVX_32B,
  reduc_AVX_64B,
  reduc_AVX_128B,
  reduc_AVX_256B,

  NULL };


//
static const void (*reduc_AVX512_fctptrs[])(run_t *) = {

  reduc_AVX512_64B,
  reduc_AVX512_128B,
  reduc_AVX512_256B,
  reduc_AVX512_512B,

  NULL };

#endif

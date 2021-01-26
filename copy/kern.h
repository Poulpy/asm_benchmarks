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
void copy_SSE_16B(run_t *run);
void copy_SSE_32B(run_t *run);
void copy_SSE_64B(run_t *run);
void copy_SSE_128B(run_t *run);

//
void copy_AVX_32B(run_t *run);
void copy_AVX_64B(run_t *run);
void copy_AVX_128B(run_t *run);
void copy_AVX_256B(run_t *run);

//
void copy_AVX512_64B(run_t *run);
void copy_AVX512_128B(run_t *run);
void copy_AVX512_256B(run_t *run);
void copy_AVX512_512B(run_t *run);

//Sizes of memory accesses per iteration for SSE kernels
static const unsigned long long copy_SSE_sizes[] = { 16, 32, 64, 128 };

//Sizes of memory accesses per iteration for AVX kernels
static const unsigned long long copy_AVX_sizes[] = { 32, 64, 128, 256 };

//Sizes of memory accesses per iteration for AVX512  kernels
static const unsigned long long copy_AVX512_sizes[] = { 64, 128, 256, 512 };

//
static const void (*copy_SSE_fctptrs[])(run_t *) = {

  copy_SSE_16B,
  copy_SSE_32B,
  copy_SSE_64B,
  copy_SSE_128B,

  NULL };

//
static const char *copy_SSE_fctnames[] = { "copy_SSE_16B", "copy_SSE_32B", "copy_SSE_64B", "copy_SSE_128B", NULL };

//
static const void (*copy_AVX_fctptrs[])(run_t *) = {

  copy_AVX_32B,
  copy_AVX_64B,
  copy_AVX_128B,
  copy_AVX_256B,

  NULL };

//
static const char *copy_AVX_fctnames[] = { "copy_AVX_32B", "copy_AVX_64B", "copy_AVX_128B", "copy_AVX_256B", NULL };

//
static const void (*copy_AVX512_fctptrs[])(run_t *) = {

  copy_AVX512_64B,
  copy_AVX512_128B,
  copy_AVX512_256B,
  copy_AVX512_512B,

  NULL };

//
static const char *copy_AVX512_fctnames[] = { "copy_AVX512_64B", "copy_AVX512_128B", "copy_AVX512_256B", "copy_AVX512_512B", NULL };

#endif

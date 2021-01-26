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
void load_SSE_16B(run_t *run);
void load_SSE_32B(run_t *run);
void load_SSE_64B(run_t *run);
void load_SSE_128B(run_t *run);

//
void load_AVX_32B(run_t *run);
void load_AVX_64B(run_t *run);
void load_AVX_128B(run_t *run);
void load_AVX_256B(run_t *run);

//
void load_AVX512_64B(run_t *run);
void load_AVX512_128B(run_t *run);
void load_AVX512_256B(run_t *run);
void load_AVX512_512B(run_t *run);

//Sizes of memory accesses per iteration for SSE kernels
static const unsigned long long load_SSE_sizes[] = { 16, 32, 64, 128 };

//Sizes of memory accesses per iteration for AVX kernels
static const unsigned long long load_AVX_sizes[] = { 32, 64, 128, 256 };

//Sizes of memory accesses per iteration for AVX512  kernels
static const unsigned long long load_AVX512_sizes[] = { 64, 128, 256, 512 };

//
static const void (*load_SSE_fctptrs[])(run_t *) = {

  load_SSE_16B,
  load_SSE_32B,
  load_SSE_64B,
  load_SSE_128B,

  NULL };

//
static const char *load_SSE_fctnames[] = { "load_SSE_16B", "load_SSE_32B", "load_SSE_64B", "load_SSE_128B", NULL };

//
static const void (*load_AVX_fctptrs[])(run_t *) = {

  load_AVX_32B,
  load_AVX_64B,
  load_AVX_128B,
  load_AVX_256B,

  NULL };

//
static const char *load_AVX_fctnames[] = { "load_AVX_32B", "load_AVX_64B", "load_AVX_128B", "load_AVX_256B", NULL };

//
static const void (*load_AVX512_fctptrs[])(run_t *) = {

  load_AVX512_64B,
  load_AVX512_128B,
  load_AVX512_256B,
  load_AVX512_512B,

  NULL };

//
static const char *load_AVX512_fctnames[] = { "load_AVX512_64B", "load_AVX512_128B", "load_AVX512_256B", "load_AVX512_512B", NULL };

#endif

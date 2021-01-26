//
#include "kern.h"

//
#include "run.h"

// SSE

//
void load_SSE_16B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //16B load
		     "movapd (%[_a_], %%rcx), %%xmm0;\n\t"
		     
		     //
		     "add $16, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "xmm0"
		     );
}

//
void load_SSE_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "movapd   (%[_a_], %%rcx), %%xmm0;\n\t"
		     "movapd 16(%[_a_], %%rcx), %%xmm1;\n\t"
		     
		     //
		     "add $32, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		   : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "xmm0", "xmm1"
		     );  
}

//
void load_SSE_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "movapd   (%[_a_], %%rcx), %%xmm0;\n\t"
		     "movapd 16(%[_a_], %%rcx), %%xmm1;\n\t"
		     "movapd 32(%[_a_], %%rcx), %%xmm2;\n\t"
		     "movapd 48(%[_a_], %%rcx), %%xmm3;\n\t"
		     
		     //
		     "add $64, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "xmm0", "xmm1", "xmm2", "xmm3"
		     ); 
}  

//
void load_SSE_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B
		     "movapd    (%[_a_], %%rcx), %%xmm0;\n\t"
		     "movapd  16(%[_a_], %%rcx), %%xmm1;\n\t"
		     "movapd  32(%[_a_], %%rcx), %%xmm2;\n\t"
		     "movapd  48(%[_a_], %%rcx), %%xmm3;\n\t"
		     "movapd  64(%[_a_], %%rcx), %%xmm4;\n\t"
		     "movapd  80(%[_a_], %%rcx), %%xmm5;\n\t"
		     "movapd  96(%[_a_], %%rcx), %%xmm6;\n\t"
		     "movapd 112(%[_a_], %%rcx), %%xmm7;\n\t"
		     
		     //
		     "add $128, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "xmm0", "xmm1", "xmm2", "xmm3",
		       "xmm4", "xmm5", "xmm6", "xmm7"
		     ); 
}  

// AVX

//
void load_AVX_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "vmovapd    (%[_a_], %%rcx), %%ymm0;\n\t"
		     
		     //
		     "add $32, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0"
		     ); 
}  

//
void load_AVX_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vmovapd    (%[_a_], %%rcx), %%ymm0;\n\t"
		     "vmovapd  32(%[_a_], %%rcx), %%ymm1;\n\t"
		     
		     //
		     "add $64, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0", "ymm1"
		     ); 
}  

//
void load_AVX_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B
		     "vmovapd    (%[_a_], %%rcx), %%ymm0;\n\t"
		     "vmovapd  32(%[_a_], %%rcx), %%ymm1;\n\t"
		     "vmovapd  64(%[_a_], %%rcx), %%ymm2;\n\t"
		     "vmovapd  96(%[_a_], %%rcx), %%ymm3;\n\t"
		     
		     //
		     "add $128, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0", "ymm1", "ymm2", "ymm3"
		     ); 
}  

//
void load_AVX_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //256B
		     "vmovapd     (%[_a_], %%rcx), %%ymm0;\n\t"
		     "vmovapd   32(%[_a_], %%rcx), %%ymm1;\n\t"
		     "vmovapd   64(%[_a_], %%rcx), %%ymm2;\n\t"
		     "vmovapd   96(%[_a_], %%rcx), %%ymm3;\n\t"
		     "vmovapd  128(%[_a_], %%rcx), %%ymm4;\n\t"
		     "vmovapd  160(%[_a_], %%rcx), %%ymm5;\n\t"
		     "vmovapd  192(%[_a_], %%rcx), %%ymm6;\n\t"
		     "vmovapd  224(%[_a_], %%rcx), %%ymm7;\n\t"
		     
		     //
		     "add $256, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0", "ymm1", "ymm2", "ymm3",
		       "ymm4", "ymm5", "ymm6", "ymm7"
		     ); 
}  

// AVX512

//
void load_AVX512_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vmovapd    (%[_a_], %%rcx), %%zmm0;\n\t"
		     
		     //
		     "add $64, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0"
		     ); 
}  

//
void load_AVX512_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B load
		     "vmovapd    (%[_a_], %%rcx), %%zmm0;\n\t"
		     "vmovapd  64(%[_a_], %%rcx), %%zmm1;\n\t"
		     
		     //
		     "add $128, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0", "zmm1"
		     ); 
}  

//
void load_AVX512_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //256B load
		     "vmovapd    (%[_a_], %%rcx), %%zmm0;\n\t"
		     "vmovapd  64(%[_a_], %%rcx), %%zmm1;\n\t"
		     "vmovapd  128(%[_a_], %%rcx), %%zmm2;\n\t"
		     "vmovapd  192(%[_a_], %%rcx), %%zmm3;\n\t"
		     
		     //
		     "add $256, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0", "zmm1", "zmm2", "zmm3"
		     ); 
}  

//
void load_AVX512_512B(run_t *run)
{  
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //512B load
		     "vmovapd     (%[_a_], %%rcx), %%zmm0;\n\t"
		     "vmovapd   64(%[_a_], %%rcx), %%zmm1;\n\t"
		     "vmovapd  128(%[_a_], %%rcx), %%zmm2;\n\t"
		     "vmovapd  192(%[_a_], %%rcx), %%zmm3;\n\t"
		     "vmovapd  256(%[_a_], %%rcx), %%zmm4;\n\t"
		     "vmovapd  320(%[_a_], %%rcx), %%zmm5;\n\t"
		     "vmovapd  384(%[_a_], %%rcx), %%zmm6;\n\t"
		     "vmovapd  448(%[_a_], %%rcx), %%zmm7;\n\t"
		     
		     //
		     "add $512, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0", "zmm1", "zmm2", "zmm3",
		       "zmm4", "zmm5", "zmm6", "zmm7"
		     ); 
}

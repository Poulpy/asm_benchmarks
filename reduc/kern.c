//
#include "kern.h"

//
#include "run.h"

// SSE

//
void reduc_SSE_16B(run_t *run)
{ 
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //16B reduc
		     "addpd (%[_a_], %%rcx), %%xmm0;\n\t"
		     
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
void reduc_SSE_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "addpd   (%[_a_], %%rcx), %%xmm0;\n\t"
		     "addpd 16(%[_a_], %%rcx), %%xmm1;\n\t"
		     
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
void reduc_SSE_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "addpd   (%[_a_], %%rcx), %%xmm0;\n\t"
		     "addpd 16(%[_a_], %%rcx), %%xmm1;\n\t"
		     "addpd 32(%[_a_], %%rcx), %%xmm2;\n\t"
		     "addpd 48(%[_a_], %%rcx), %%xmm3;\n\t"
		     
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
void reduc_SSE_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B
		     "addpd    (%[_a_], %%rcx), %%xmm0;\n\t"
		     "addpd  16(%[_a_], %%rcx), %%xmm1;\n\t"
		     "addpd  32(%[_a_], %%rcx), %%xmm2;\n\t"
		     "addpd  48(%[_a_], %%rcx), %%xmm3;\n\t"
		     "addpd  64(%[_a_], %%rcx), %%xmm4;\n\t"
		     "addpd  80(%[_a_], %%rcx), %%xmm5;\n\t"
		     "addpd  96(%[_a_], %%rcx), %%xmm6;\n\t"
		     "addpd 112(%[_a_], %%rcx), %%xmm7;\n\t"
		     
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
void reduc_AVX_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "vaddpd    (%[_a_], %%rcx), %%ymm0, %%ymm0;\n\t"
		     
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
void reduc_AVX_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vaddpd    (%[_a_], %%rcx), %%ymm0, %%ymm0;\n\t"
		     "vaddpd  32(%[_a_], %%rcx), %%ymm1, %%ymm1;\n\t"
		     
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
void reduc_AVX_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B
		     "vaddpd    (%[_a_], %%rcx), %%ymm0, %%ymm0;\n\t"
		     "vaddpd  32(%[_a_], %%rcx), %%ymm1, %%ymm1;\n\t"
		     "vaddpd  64(%[_a_], %%rcx), %%ymm2, %%ymm2;\n\t"
		     "vaddpd  96(%[_a_], %%rcx), %%ymm3, %%ymm3;\n\t"
		     
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
void reduc_AVX_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //256B
		     "vaddpd     (%[_a_], %%rcx), %%ymm0, %%ymm0;\n\t"
		     "vaddpd   32(%[_a_], %%rcx), %%ymm1, %%ymm1;\n\t"
		     "vaddpd   64(%[_a_], %%rcx), %%ymm2, %%ymm2;\n\t"
		     "vaddpd   96(%[_a_], %%rcx), %%ymm3, %%ymm3;\n\t"
		     "vaddpd  128(%[_a_], %%rcx), %%ymm4, %%ymm4;\n\t"
		     "vaddpd  160(%[_a_], %%rcx), %%ymm5, %%ymm5;\n\t"
		     "vaddpd  192(%[_a_], %%rcx), %%ymm6, %%ymm6;\n\t"
		     "vaddpd  224(%[_a_], %%rcx), %%ymm7, %%ymm7;\n\t"
		     
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
void reduc_AVX512_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vaddpd    (%[_a_], %%rcx), %%zmm0, %%zmm0;\n\t"
		     
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
void reduc_AVX512_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B reduc
		     "vaddpd    (%[_a_], %%rcx), %%zmm0, %%zmm0;\n\t"
		     "vaddpd  64(%[_a_], %%rcx), %%zmm1, %%zmm1;\n\t"
		     
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
void reduc_AVX512_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //256B reduc
		     "vaddpd     (%[_a_], %%rcx), %%zmm0, %%zmm0;\n\t"
		     "vaddpd   64(%[_a_], %%rcx), %%zmm1, %%zmm1;\n\t"
		     "vaddpd  128(%[_a_], %%rcx), %%zmm2, %%zmm2;\n\t"
		     "vaddpd  192(%[_a_], %%rcx), %%zmm3, %%zmm3;\n\t"
		     
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
void reduc_AVX512_512B(run_t *run)
{  
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //512B reduc
		     "vaddpd     (%[_a_], %%rcx), %%zmm0, %%zmm0;\n\t"
		     "vaddpd   64(%[_a_], %%rcx), %%zmm1, %%zmm1;\n\t"
		     "vaddpd  128(%[_a_], %%rcx), %%zmm2, %%zmm2;\n\t"
		     "vaddpd  192(%[_a_], %%rcx), %%zmm3, %%zmm3;\n\t"
		     "vaddpd  256(%[_a_], %%rcx), %%zmm4, %%zmm4;\n\t"
		     "vaddpd  320(%[_a_], %%rcx), %%zmm5, %%zmm5;\n\t"
		     "vaddpd  384(%[_a_], %%rcx), %%zmm6, %%zmm6;\n\t"
		     "vaddpd  448(%[_a_], %%rcx), %%zmm7, %%zmm7;\n\t"
		     
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

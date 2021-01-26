//
#include "kern.h"

//
#include "run.h"

// SSE

//
void ntstore_SSE_16B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     "xorpd %%xmm0, %%xmm0;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //16B load
		     "movntpd %%xmm0, (%[_a_], %%rcx);\n\t"
		     
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
void ntstore_SSE_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"

		     "xorpd %%xmm0, %%xmm0;\n\t"
		     "xorpd %%xmm1, %%xmm1;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "movntpd %%xmm0,   (%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm1, 16(%[_a_], %%rcx);\n\t"
		     
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
void ntstore_SSE_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     "xorpd %%xmm0, %%xmm0;\n\t"
		     "xorpd %%xmm1, %%xmm1;\n\t"
		     "xorpd %%xmm2, %%xmm2;\n\t"
		     "xorpd %%xmm3, %%xmm3;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "movntpd %%xmm0,   (%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm1, 16(%[_a_], %%rcx);\n\t"		     
		     "movntpd %%xmm2, 32(%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm3, 48(%[_a_], %%rcx);\n\t"
		     
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
void ntstore_SSE_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"

		     "xorpd %%xmm0, %%xmm0;\n\t"
		     "xorpd %%xmm1, %%xmm1;\n\t"
		     "xorpd %%xmm2, %%xmm2;\n\t"
		     "xorpd %%xmm3, %%xmm3;\n\t"
		     "xorpd %%xmm4, %%xmm4;\n\t"
		     "xorpd %%xmm5, %%xmm5;\n\t"
		     "xorpd %%xmm6, %%xmm6;\n\t"
		     "xorpd %%xmm7, %%xmm7;\n\t"

		     //
		     "1:\n\t"
		     
		     //128B
		     "movntpd %%xmm0,    (%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm1,  16(%[_a_], %%rcx);\n\t"		     
		     "movntpd %%xmm2,  32(%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm3,  48(%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm4,  64(%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm5,  80(%[_a_], %%rcx);\n\t"		     
		     "movntpd %%xmm6,  96(%[_a_], %%rcx);\n\t"
		     "movntpd %%xmm7, 112(%[_a_], %%rcx);\n\t"

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
void ntstore_AVX_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"

		     "vxorpd %%ymm0, %%ymm0, %%ymm0;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "vmovntpd    %%ymm0, (%[_a_], %%rcx);\n\t"
		     
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
void ntstore_AVX_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"

		     "vxorpd %%ymm0, %%ymm0, %%ymm0;\n\t"
		     "vxorpd %%ymm1, %%ymm1, %%ymm1;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vmovntpd    %%ymm0,   (%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm1, 32(%[_a_], %%rcx);\n\t"
		     
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
void ntstore_AVX_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     "vxorpd %%ymm0, %%ymm0, %%ymm0;\n\t"
		     "vxorpd %%ymm1, %%ymm1, %%ymm1;\n\t"
		     "vxorpd %%ymm2, %%ymm2, %%ymm2;\n\t"
		     "vxorpd %%ymm3, %%ymm3, %%ymm3;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B
		     "vmovntpd    %%ymm0,   (%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm1, 32(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm2, 64(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm3, 96(%[_a_], %%rcx);\n\t"
		     
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
void ntstore_AVX_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"

		     "vxorpd %%ymm0, %%ymm0, %%ymm0;\n\t"
		     "vxorpd %%ymm1, %%ymm1, %%ymm1;\n\t"
		     "vxorpd %%ymm2, %%ymm2, %%ymm2;\n\t"
		     "vxorpd %%ymm3, %%ymm3, %%ymm3;\n\t"
		     "vxorpd %%ymm4, %%ymm4, %%ymm4;\n\t"
		     "vxorpd %%ymm5, %%ymm5, %%ymm5;\n\t"
		     "vxorpd %%ymm6, %%ymm6, %%ymm6;\n\t"
		     "vxorpd %%ymm7, %%ymm7, %%ymm7;\n\t"

		     //
		     "1:\n\t"
		     
		     //256B
		     "vmovntpd    %%ymm0,    (%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm1,  32(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm2,  64(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm3,  96(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm4, 128(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm5, 160(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm6, 192(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%ymm7, 224(%[_a_], %%rcx);\n\t"

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
void ntstore_AVX512_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"

		     "vxorpd %%zmm0, %%zmm0, %%zmm0;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vmovntpd    %%zmm0, (%[_a_], %%rcx);\n\t"
		     
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
void ntstore_AVX512_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     "vxorpd %%zmm0, %%zmm0, %%zmm0;\n\t"
		     "vxorpd %%zmm1, %%zmm1, %%zmm1;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B
		     "vmovntpd    %%zmm0,   (%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm1, 64(%[_a_], %%rcx);\n\t"
		     
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
void ntstore_AVX512_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     "vxorpd %%zmm0, %%zmm0, %%zmm0;\n\t"
		     "vxorpd %%zmm1, %%zmm1, %%zmm1;\n\t"
		     "vxorpd %%zmm2, %%zmm2, %%zmm2;\n\t"
		     "vxorpd %%zmm3, %%zmm3, %%zmm3;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //256B
		     "vmovntpd    %%zmm0,    (%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm1,  64(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm2, 128(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm3, 192(%[_a_], %%rcx);\n\t"
		     
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
void ntstore_AVX512_512B(run_t *run)
{  
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     "vxorpd %%zmm0, %%zmm0, %%zmm0;\n\t"
		     "vxorpd %%zmm1, %%zmm1, %%zmm1;\n\t"
		     "vxorpd %%zmm2, %%zmm2, %%zmm2;\n\t"
		     "vxorpd %%zmm3, %%zmm3, %%zmm3;\n\t"
		     "vxorpd %%zmm4, %%zmm4, %%zmm4;\n\t"
		     "vxorpd %%zmm5, %%zmm5, %%zmm5;\n\t"
		     "vxorpd %%zmm6, %%zmm6, %%zmm6;\n\t"
		     "vxorpd %%zmm7, %%zmm7, %%zmm7;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //512B
		     "vmovntpd    %%zmm0,    (%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm1,  64(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm2, 128(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm3, 192(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm4, 256(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm5, 320(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm6, 384(%[_a_], %%rcx);\n\t"
		     "vmovntpd    %%zmm7, 448(%[_a_], %%rcx);\n\t"
		     
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

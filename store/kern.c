//
#include "kern.h"

//
#include "run.h"

// SSE

//
void store_SSE_16B(run_t *run)
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
		     "movapd %%xmm0, (%[_a_], %%rcx);\n\t"
		     
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
void store_SSE_32B(run_t *run)
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
		     "movapd %%xmm0,   (%[_a_], %%rcx);\n\t"
		     "movapd %%xmm1, 16(%[_a_], %%rcx);\n\t"
		     
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
void store_SSE_64B(run_t *run)
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
		     "movapd %%xmm0,   (%[_a_], %%rcx);\n\t"
		     "movapd %%xmm1, 16(%[_a_], %%rcx);\n\t"		     
		     "movapd %%xmm2, 32(%[_a_], %%rcx);\n\t"
		     "movapd %%xmm3, 48(%[_a_], %%rcx);\n\t"
		     
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
void store_SSE_128B(run_t *run)
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
		     "movapd %%xmm0,    (%[_a_], %%rcx);\n\t"
		     "movapd %%xmm1,  16(%[_a_], %%rcx);\n\t"		     
		     "movapd %%xmm2,  32(%[_a_], %%rcx);\n\t"
		     "movapd %%xmm3,  48(%[_a_], %%rcx);\n\t"
		     "movapd %%xmm4,  64(%[_a_], %%rcx);\n\t"
		     "movapd %%xmm5,  80(%[_a_], %%rcx);\n\t"		     
		     "movapd %%xmm6,  96(%[_a_], %%rcx);\n\t"
		     "movapd %%xmm7, 112(%[_a_], %%rcx);\n\t"

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
void store_AVX_32B(run_t *run)
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
		     "vmovapd    %%ymm0, (%[_a_], %%rcx);\n\t"
		     
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
void store_AVX_64B(run_t *run)
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
		     "vmovapd    %%ymm0,   (%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm1, 32(%[_a_], %%rcx);\n\t"
		     
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
void store_AVX_128B(run_t *run)
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
		     "vmovapd    %%ymm0,   (%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm1, 32(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm2, 64(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm3, 96(%[_a_], %%rcx);\n\t"
		     
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
void store_AVX_256B(run_t *run)
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
		     "vmovapd    %%ymm0,    (%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm1,  32(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm2,  64(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm3,  96(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm4, 128(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm5, 160(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm6, 192(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%ymm7, 224(%[_a_], %%rcx);\n\t"

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
void store_AVX512_64B(run_t *run)
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
		     "vmovapd    %%zmm0, (%[_a_], %%rcx);\n\t"
		     
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
void store_AVX512_128B(run_t *run)
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
		     "vmovapd    %%zmm0,   (%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm1, 64(%[_a_], %%rcx);\n\t"
		     
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
void store_AVX512_256B(run_t *run)
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
		     "vmovapd    %%zmm0,    (%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm1,  64(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm2, 128(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm3, 192(%[_a_], %%rcx);\n\t"
		     
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
void store_AVX512_512B(run_t *run)
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
		     "vmovapd    %%zmm0,    (%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm1,  64(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm2, 128(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm3, 192(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm4, 256(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm5, 320(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm6, 384(%[_a_], %%rcx);\n\t"
		     "vmovapd    %%zmm7, 448(%[_a_], %%rcx);\n\t"
		     
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

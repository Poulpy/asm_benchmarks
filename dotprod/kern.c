//
#include "kern.h"

//
#include "run.h"

// SSE

//
void dotprod_SSE_16B(run_t *run)
{ 
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //16B dotprod
		     "vmovapd     (%[_a_], %%rcx), %%xmm1;\n\t"
		     "vfmadd231pd (%[_b_], %%rcx), %%xmm1, %%xmm0;\n\t"
		     
		     //
		     "add $16, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "xmm0", "xmm1"
		     );
}

//
void dotprod_SSE_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "vmovapd       (%[_a_], %%rcx), %%xmm2;\n\t"
		     "vmovapd     16(%[_a_], %%rcx), %%xmm3;\n\t"
		     "vfmadd231pd   (%[_b_], %%rcx), %%xmm2, %%xmm0;\n\t"
		     "vfmadd231pd 16(%[_b_], %%rcx), %%xmm3, %%xmm1;\n\t"
		     		     
		     //
		     "add $32, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "xmm0", "xmm1", "xmm2", "xmm3"
		     );  
}

//
void dotprod_SSE_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     //32B
		     "vmovapd       (%[_a_], %%rcx), %%xmm4;\n\t"
		     "vmovapd     16(%[_a_], %%rcx), %%xmm5;\n\t"
		     "vmovapd     32(%[_a_], %%rcx), %%xmm6;\n\t"
		     "vmovapd     48(%[_a_], %%rcx), %%xmm7;\n\t"
		     "vfmadd231pd   (%[_b_], %%rcx), %%xmm4, %%xmm0;\n\t"
		     "vfmadd231pd 16(%[_b_], %%rcx), %%xmm5, %%xmm1;\n\t"
		     "vfmadd231pd 32(%[_b_], %%rcx), %%xmm6, %%xmm2;\n\t"
		     "vfmadd231pd 48(%[_b_], %%rcx), %%xmm7, %%xmm3;\n\t"
		     
		     //
		     "add $64, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "xmm0", "xmm1", "xmm2", "xmm3",
		       "xmm4", "xmm5", "xmm6", "xmm7"		       
		     ); 
}

// AVX

//
void dotprod_AVX_32B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //32B
		     "vmovapd       (%[_a_], %%rcx), %%ymm1;\n\t"
		     "vfmadd231pd   (%[_b_], %%rcx), %%ymm1, %%ymm0;\n\t"
		     
		     //
		     "add $32, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0", "ymm1"
		     ); 
}  

//
void dotprod_AVX_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vmovapd         (%[_a_], %%rcx), %%ymm2;\n\t"
		     "vmovapd       32(%[_a_], %%rcx), %%ymm3;\n\t"
		     "vfmadd231pd     (%[_b_], %%rcx), %%ymm2, %%ymm0;\n\t"
		     "vfmadd231pd   32(%[_b_], %%rcx), %%ymm3, %%ymm1;\n\t"
		     		     
		     //
		     "add $64, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0", "ymm1", "ymm2", "ymm3"
		     ); 
}  

//
void dotprod_AVX_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B
		     "vmovapd         (%[_a_], %%rcx), %%ymm4;\n\t"
		     "vmovapd       32(%[_a_], %%rcx), %%ymm5;\n\t"
		     "vmovapd       64(%[_a_], %%rcx), %%ymm6;\n\t"
		     "vmovapd       96(%[_a_], %%rcx), %%ymm7;\n\t"
		     "vfmadd231pd     (%[_b_], %%rcx), %%ymm4, %%ymm0;\n\t"
		     "vfmadd231pd   32(%[_b_], %%rcx), %%ymm5, %%ymm1;\n\t"
		     "vfmadd231pd   64(%[_b_], %%rcx), %%ymm6, %%ymm2;\n\t"
		     "vfmadd231pd   96(%[_b_], %%rcx), %%ymm7, %%ymm3;\n\t"
		     
		     //
		     "add $128, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0", "ymm1", "ymm2", "ymm3",
		       "ymm4", "ymm5", "ymm6", "ymm7"
		     ); 
}  

//
void dotprod_AVX_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //256B
		     "vmovapd         (%[_a_], %%rcx), %%ymm8;\n\t"
		     "vmovapd       32(%[_a_], %%rcx), %%ymm9;\n\t"
		     "vmovapd       64(%[_a_], %%rcx), %%ymm10;\n\t"
		     "vmovapd       96(%[_a_], %%rcx), %%ymm11;\n\t"
		     "vmovapd      128(%[_a_], %%rcx), %%ymm12;\n\t"
		     "vmovapd      160(%[_a_], %%rcx), %%ymm13;\n\t"
		     "vmovapd      192(%[_a_], %%rcx), %%ymm14;\n\t"
		     "vmovapd      224(%[_a_], %%rcx), %%ymm15;\n\t"

		     "vfmadd231pd     (%[_b_], %%rcx), %%ymm8, %%ymm0;\n\t"
		     "vfmadd231pd   32(%[_b_], %%rcx), %%ymm9, %%ymm1;\n\t"
		     "vfmadd231pd   64(%[_b_], %%rcx), %%ymm10, %%ymm2;\n\t"
		     "vfmadd231pd   96(%[_b_], %%rcx), %%ymm11, %%ymm3;\n\t"
		     "vfmadd231pd  128(%[_b_], %%rcx), %%ymm12, %%ymm4;\n\t"
		     "vfmadd231pd  160(%[_b_], %%rcx), %%ymm13, %%ymm5;\n\t"
		     "vfmadd231pd  192(%[_b_], %%rcx), %%ymm14, %%ymm6;\n\t"
		     "vfmadd231pd  224(%[_b_], %%rcx), %%ymm15, %%ymm7;\n\t"
		     
		     //
		     "add $256, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "ymm0", "ymm1", "ymm2", "ymm3",
		       "ymm4", "ymm5", "ymm6", "ymm7",
		       "ymm8", "ymm9", "ymm10", "ymm11",
		       "ymm12", "ymm13", "ymm14", "ymm15"
		       
		     ); 
}  

// AVX512

//
void dotprod_AVX512_64B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //64B
		     "vmovapd        (%[_a_], %%rcx), %%zmm1;\n\t"
		     "vfmadd231pd    (%[_a_], %%rcx), %%zmm0, %%zmm0;\n\t"
		     
		     //
		     "add $64, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0", "zmm1"
		     ); 
}  

//
void dotprod_AVX512_128B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //128B dotprod
		     "vmovapd        (%[_a_], %%rcx), %%zmm2;\n\t"
		     "vmovapd      64(%[_a_], %%rcx), %%zmm3;\n\t"
		     "vfmadd231pd    (%[_b_], %%rcx), %%zmm2, %%zmm0;\n\t"
		     "vfmadd231pd  64(%[_b_], %%rcx), %%zmm3, %%zmm1;\n\t"
		     
		     //
		     "add $128, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0", "zmm1", "zmm2", "zmm3"
		     ); 
}  

//
void dotprod_AVX512_256B(run_t *run)
{
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //256B dotprod
		     "vmovapd        (%[_a_], %%rcx), %%zmm4;\n\t"
		     "vmovapd      64(%[_a_], %%rcx), %%zmm5;\n\t"
		     "vmovapd     128(%[_a_], %%rcx), %%zmm6;\n\t"
		     "vmovapd     192(%[_a_], %%rcx), %%zmm7;\n\t"
		     "vfmadd231pd    (%[_b_], %%rcx), %%zmm4, %%zmm0;\n\t"
		     "vfmadd231pd  64(%[_b_], %%rcx), %%zmm5, %%zmm1;\n\t"
		     "vfmadd231pd 128(%[_b_], %%rcx), %%zmm6, %%zmm2;\n\t"
		     "vfmadd231pd 192(%[_b_], %%rcx), %%zmm7, %%zmm3;\n\t"
		     
		     //
		     "add $256, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0", "zmm1", "zmm2", "zmm3",
		       "zmm4", "zmm5", "zmm6", "zmm7"
		     ); 
}  

//
void dotprod_AVX512_512B(run_t *run)
{  
  //
  for (unsigned long long i = 0; i < run->r; i++)
    __asm__ volatile(
		     //
		     "xor %%rcx, %%rcx;\n\t"
		     
		     //
		     "1:\n\t"
		     
		     //512B dotprod
		     "vmovapd        (%[_a_], %%rcx), %%zmm8;\n\t"
		     "vmovapd      64(%[_a_], %%rcx), %%zmm9;\n\t"
		     "vmovapd     128(%[_a_], %%rcx), %%zmm10;\n\t"
		     "vmovapd     192(%[_a_], %%rcx), %%zmm11;\n\t"
		     "vmovapd     256(%[_a_], %%rcx), %%zmm12;\n\t"
		     "vmovapd     320(%[_a_], %%rcx), %%zmm13;\n\t"
		     "vmovapd     384(%[_a_], %%rcx), %%zmm14;\n\t"
		     "vmovapd     448(%[_a_], %%rcx), %%zmm15;\n\t"
		     "vfmadd231pd    (%[_b_], %%rcx), %%zmm8, %%zmm0;\n\t"
		     "vfmadd231pd  64(%[_b_], %%rcx), %%zmm9, %%zmm1;\n\t"
		     "vfmadd231pd 128(%[_b_], %%rcx), %%zmm10, %%zmm2;\n\t"
		     "vfmadd231pd 192(%[_b_], %%rcx), %%zmm11, %%zmm3;\n\t"
		     "vfmadd231pd 256(%[_b_], %%rcx), %%zmm12, %%zmm4;\n\t"
		     "vfmadd231pd 320(%[_b_], %%rcx), %%zmm13, %%zmm5;\n\t"
		     "vfmadd231pd 384(%[_b_], %%rcx), %%zmm14, %%zmm6;\n\t"
		     "vfmadd231pd 448(%[_b_], %%rcx), %%zmm15, %%zmm7;\n\t"
		     
		     //
		     "add $512, %%rcx;\n\t"
		     "cmp %[_s_], %%rcx;\n\t"
		     "jl 1b;\n\t"
		     
		     : //output
		     : //input
		       [_a_] "r" (run->a[0]),
		       [_b_] "r" (run->a[1]),
		       [_s_] "r" (run->s)
		     : //clobber
		       "cc", "memory", "rcx",
		       "zmm0", "zmm1", "zmm2", "zmm3",
		       "zmm4", "zmm5", "zmm6", "zmm7",
		       "zmm8", "zmm9", "zmm10", "zmm11",
		       "zmm12", "zmm13", "zmm14", "zmm15"
		     ); 
}

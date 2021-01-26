CC=gcc

CFLAGS=-Wall -g3

OFLAGS=-march=native -mtune=native -Ofast

FILES=reduc.c kern.c run.c stats.c

all: reduc_SSE_AVX

avx512: reduc_SSE_AVX_AVX512

reduc_SSE_AVX: $(FILES)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

reduc_SSE_AVX_AVX512:
	$(CC) -DAVX512=1 $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

clean:
	rm -Rf reduc_*

CC=gcc

CFLAGS=-Wall -g3

OFLAGS=-march=native -mtune=native -Ofast

FILES=triad.c kern.c run.c stats.c

all: triad_SSE_AVX

avx512: triad_SSE_AVX_AVX512

triad_SSE_AVX: $(FILES)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

triad_SSE_AVX_AVX512:
	$(CC) -DAVX512=1 $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

clean:
	rm -Rf triad_*

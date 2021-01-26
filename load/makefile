CC=gcc

CFLAGS=-Wall -g3

OFLAGS=-march=native -mtune=native -Ofast

FILES=load.c kern.c run.c stats.c

all: load_SSE_AVX

avx512: load_SSE_AVX_AVX512

load_SSE_AVX: $(FILES)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

load_SSE_AVX_AVX512:
	$(CC) -DAVX512=1 $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

clean:
	rm -Rf load_*

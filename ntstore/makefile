CC=gcc

CFLAGS=-Wall -g3

OFLAGS=-march=native -mtune=native -Ofast

FILES=ntstore.c kern.c run.c stats.c

all: ntstore_SSE_AVX

avx512: ntstore_SSE_AVX_AVX512

ntstore_SSE_AVX: $(FILES)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

ntstore_SSE_AVX_AVX512:
	$(CC) -DAVX512=1 $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

clean:
	rm -Rf ntstore_*

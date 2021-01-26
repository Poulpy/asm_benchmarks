CC=gcc

CFLAGS=-Wall -g3

OFLAGS=-march=native -mtune=native -Ofast

FILES=copy.c kern.c run.c stats.c

all: copy_SSE_AVX

avx512: copy_SSE_AVX_AVX512

copy_SSE_AVX: $(FILES)
	$(CC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

copy_SSE_AVX_AVX512:
	$(CC) -DAVX512=1 $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

clean:
	rm -Rf copy_*

GCC=gcc

CFLAGS=-Wall -g

OFLAGS=-O3

FILES=memcpy.c stats.c

all: memcpy

memcpy: $(FILES)
	$(GCC) $(CFLAGS) $(OFLAGS) $(FILES) -o $@ -lm

clean: memcpy
	@clean
	@rm $<

cpupower -c 3 frequency-set --governor performance
# cpupower -c 3 frequency-set --freq
cd copy/ && make && taskset -c 3 ./copy_SSE_AVX 24576 1000 | cut -d';' -f1,9
cd dotprod/ && make && taskset -c 3 ./dotprod_SSE_AVX 24576 1000 | cut -d';' -f1,9
cd load/ && make && taskset -c 3 ./load_SSE_AVX 24576 1000 | cut -d';' -f1,9
cd ntstore/ && make && taskset -c 3 ./ntstore_SSE_AVX 24576 1000 | cut -d';' -f1,9
cd reduc/ && make && taskset -c 3 ./reduc_SSE_AVX 24576 1000 | cut -d';' -f1,9
cd store/ && make && taskset -c 3 ./store_SSE_AVX 24576 1000 | cut -d';' -f1,9
cd triad/ && make && taskset -c 3 ./triad_SSE_AVX 24576 1000 | cut -d';' -f1,9

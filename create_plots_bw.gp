set term png size 1900,1000 enhanced font "Terminal,10"

set grid

set auto x

set key left top

set title "Intel(R) Pentium(R) bandwidth (in GiB/s) for a Load benchmark on a single array"

set xlabel "Benchmark variants"
set ylabel "Bandwidth in GiB/s (higher is better)"

set style data histogram
set style fill solid border -1
set boxwidth 0.9

set xtic rotate by -45 scale 0

set multiplot layout 3, 2 rowsfirst

set yrange [0:100]

set title "load benchmarks"
plot "load/load_L1.dat" u 2:xtic(1) t "L1", "load/load_L2.dat" u 2:xtic(1) t "L2"
set title "copy benchmarks"
plot "copy/copy_L1.dat" u 2:xtic(1) t "L1", "copy/copy_L2.dat" u 2:xtic(1) t "L2"
set title "store benchmarks"
plot "store/store_L1.dat" u 2:xtic(1) t "L1", "store/store_L2.dat" u 2:xtic(1) t "L2"
set title "ntstore benchmarks"
plot "ntstore/ntstore_L1.dat" u 2:xtic(1) t "L1", "ntstore/ntstore_L2.dat" u 2:xtic(1) t "L2"
set title "memcpy benchmarks"
plot "memcpy/memcpy_L1.dat" u 2:xtic(1) t "L1", "memcpy/memcpy_L2.dat" u 2:xtic(1) t "L2"
set title "reduc benchmarks"
plot "reduc/reduc_L1.dat" u 2:xtic(1) t "L1", "reduc/reduc_L2.dat" u 2:xtic(1) t "L2"


unset multiplot

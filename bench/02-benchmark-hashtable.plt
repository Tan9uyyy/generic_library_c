HEAD="02-benchmark-hashtable"

load "bench/common.plt" # Common plot options

# First plot
set key top left
set output "bench/hashtable_put.png"
set title "Hashtable put"

plot \
    "bench/" . HEAD . ".csv"    using 1:2 with lines ls 101 title "closed",\
    ''                          using 1:3 with lines ls 102 title "linear",



HEAD="06-benchmark-set"

load "bench/common.plt"

set key top left
set output "bench/set_put.png"
set title "Set Put"

plot \
    "bench/" . HEAD . ".csv"    using 1:2 with lines ls 101 title "treeset",\
    ''                          using 1:3 with lines ls 102 title "hashtable"

set key top left
set output "bench/set_contains.png"
set title "Set Contains"

plot \
    "bench/" . HEAD . ".csv"    using 1:4 with lines ls 101 title "treeset",\
    ''                          using 1:5 with lines ls 102 title "hashtable"

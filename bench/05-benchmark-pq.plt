HEAD="05-benchmark-pq"

load "bench/common.plt"

set key top left
set output "bench/pq_push.png"
set title "Priority Queue Push"

plot \
    "bench/" . HEAD . ".csv"    using 1:2 with lines ls 101 title "linked pq",\
    ''                          using 1:3 with lines ls 102 title "heap"

set key top left
set output "bench/pq_pop.png"
set title "Priority Queue Pop"

plot \
    "bench/" . HEAD . ".csv"    using 1:4 with lines ls 101 title "linked pq",\
    ''                          using 1:5 with lines ls 102 title "heap"

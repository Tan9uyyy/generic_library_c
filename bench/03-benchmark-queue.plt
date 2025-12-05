HEAD="03-benchmark-queue"

load "bench/common.plt"

set key top left
set output "bench/queue_push.png"
set title "Queue Push"

plot \
    "bench/" . HEAD . ".csv"    using 1:2 with lines ls 101 title "linked queue",\
    ''                          using 1:3 with lines ls 102 title "array deque"

set key top left
set output "bench/queue_pop.png"
set title "Queue Pop"

plot \
    "bench/" . HEAD . ".csv"    using 1:4 with lines ls 101 title "linked queue",\
    ''                          using 1:5 with lines ls 102 title "array deque"

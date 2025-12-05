HEAD="04-benchmark-stack"

load "bench/common.plt"

set key top left
set output "bench/stack_push.png"
set title "Stack Push"

plot \
    "bench/" . HEAD . ".csv"    using 1:2 with lines ls 101 title "linked stack",\
    ''                          using 1:3 with lines ls 102 title "array deque"

set key top left
set output "bench/stack_pop.png"
set title "Stack Pop"

plot \
    "bench/" . HEAD . ".csv"    using 1:4 with lines ls 101 title "linked stack",\
    ''                          using 1:5 with lines ls 102 title "array deque"

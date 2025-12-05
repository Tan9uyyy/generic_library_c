HEAD="01-benchmark-deque"

load "bench/common.plt" # Common plot options

# First plot
set key top left
set output "bench/deque_push_front.png"
set title "Push front"

plot \
    "bench/" . HEAD . ".csv"    using 1:2 with lines ls 101 title "linked deque",\
    ''                          using 1:3 with lines ls 102 title "array deque"



# Second plot
set key right top
set output "bench/deque_push_back.png"
set title "Push back"

plot \
    "bench/" . HEAD . ".csv"    using 1:4 with lines ls 102 title "linked deque",\
    ''                          using 1:5 with lines ls 103 title "array deque"

# Third plot
set key top left
set output "bench/deque_pop_front.png"
set title "Pop front"

plot \
    "bench/" . HEAD . ".csv"    using 1:6 with lines ls 103 title "linked deque",\
    ''                          using 1:7 with lines ls 104 title "array deque"



# Forth plot
set key right top
set output "bench/deque_pop_back.png"
set title "Pop back"

plot \
    "bench/" . HEAD . ".csv"    using 1:8 with lines ls 104 title "linked deque",\
    ''                          using 1:9 with lines ls 105 title "array deque"



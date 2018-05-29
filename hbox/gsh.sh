ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | wc -l

./tests/putc-driver Makefile logs/some & ./tests/putc-driver Makefile logs/some2

diff logs/some logs/some2

dd if=/dev/urandom of=logs/gshtest bs=1 count=1000000 2>/dev/null

dd if=/dev/urandom of=logs/gshtest2 bs=1 count=1000000 2>/dev/null

dd if=/dev/urandom of=logs/gshtest3 bs=1 count=1000000 2>/dev/null

./tests/putc-driver logs/gshtest logs/gshtest-control & ./tests/putc-driver logs/gshtest2 logs/gshtest-control2 & ./tests/putc-driver logs/gshtest3 logs/gshtest-control3

diff logs/gshtest logs/gshtest-control

diff logs/gshtest2 logs/gshtest-control2







ls | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l | wc -l

./tests/putc-driver Makefile logs/some & ./tests/putc-driver Makefile logs/some2

diff logs/some logs/some2

./hbox/make_temps.sh

./tests/putc-driver logs/gshtest logs/gshtest-control & ./tests/putc-driver logs/gshtest2 logs/gshtest-control2 & ./tests/putc-driver logs/gshtest3 logs/gshtest-control3

sleep 4

diff logs/gshtest logs/gshtest-control

diff logs/gshtest2 logs/gshtest-control2

diff logs/gshtest3 logs/gshtest-control3



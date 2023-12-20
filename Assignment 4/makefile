# Michael Sirna
# 1094947
# 2023-11-24
# CIS3090 Assignment 4

all: graphics ng

graphics: graphics.c
	gcc graphics.c -o graphics -lncurses -lm  /usr/lib/x86_64-linux-gnu/libOpenCL.so.1.0.0

ng: graphics.c
	gcc graphics.c -o ng -DNOGRAPHICS -lm  /usr/lib/x86_64-linux-gnu/libOpenCL.so.1.0.0

clean:
	rm graphics



# Makefile for the lab assignment
# You are NOT supposed to modify this
# file.

all: server simplefork server1 server2

server: server.c netstuff.h liblab1.a
	@echo "Compiling server.c"
	@gcc -Wall -Werror -m32 server.c -o server  -L. -llab1

server1: server1.c netstuff.h liblab1.a
	@echo "Compiling server1.c"
	@gcc -Wall -Werror -m32 server1.c -o server1 -L. -llab1

server2: server2.c netstuff.h liblab1.a
	@echo "Compiling server2.c"
	@gcc -Wall -Werror -m32 server2.c -o server2 -L. -llab1

simplefork: simplefork.c
	@echo "Compiling simplefork.c"
	@gcc -Wall -Werror -m32 simplefork.c -o simplefork

CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror -Wno-unused-variable $< -o $@

all: fortune hello

fortune : hello.c
	gcc fortune.c -o fortune

hello : hello.c
	gcc hello.c -o hello

clean :
	rm hello fortune

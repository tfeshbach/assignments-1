CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror $< -o $@

all : test_ppm ascii_image

clean :
	rm test_ppm ascii_image 2> /dev/null

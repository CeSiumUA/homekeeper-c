GNULIBS = -ltelebot
INCLUDES = -Iinc
CFLAGS = $(INCLUDES) -Wall -Werror
SRCS = src/*.c

.PHONY:
	build

build:
	cc -o main $(SRCS) $(CFLAGS) $(GNULIBS)

clean:
	rm ./main
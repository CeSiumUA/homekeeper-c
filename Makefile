GNULIBS = -ltelebot
INCLUDES = -I /inc
CFLAGS = $(INCLUDES) -Wall -Werror
SRCS = src/*.c

.PHONY:
	build

build:
	cc -o main $(SRCS) $(CFLAGS) $(GNULIBS)

clean:
	rm ./main
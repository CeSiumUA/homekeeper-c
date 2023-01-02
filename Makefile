GCC = gcc
TLLIB = -ltelebot
INCLUDES = -Iinc
CFLAGS = $(INCLUDES) -g -Wall -Werror -o a.out
SRCS = src/*.c

.PHONY: build

all: build

build:
	$(GCC) $(SRCS) $(CFLAGS) $(TLLIB)

clean:
	rm ./a.out
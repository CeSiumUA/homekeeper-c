GCC = gcc
LIBS = -ltelebot -lpthread
INCLUDES = -Iinc
CFLAGS = $(INCLUDES) -g -Wall -Werror -o a.out
SRCS = src/*.c

.PHONY: build

all: build

build:
	$(GCC) $(SRCS) $(CFLAGS) $(LIBS)

clean:
	rm ./a.out
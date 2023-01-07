GCC = gcc
LIBS = -ltelebot -lpthread
INCLUDES = -Iinc -Iinc/ed_crypto
CFLAGS = $(INCLUDES) -g -Wall -Werror -o a.out
SRCS = src/*.c src/ed_crypto/*.c

.PHONY: build

all: build

build:
	$(GCC) $(SRCS) $(CFLAGS) $(LIBS)

clean:
	rm ./a.out
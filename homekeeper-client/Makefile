GCC = gcc
INCLUDES = -Iinc -Iinc/ed_crypto
CFLAGS = $(INCLUDES) -g -Wall -Werror -o homekeeper-client
SRCS = src/*.c src/ed_crypto/*.c

.PHONY: build

all: build

build:
	$(GCC) $(SRCS) $(CFLAGS)

clean:
	rm ./homekeeper-client
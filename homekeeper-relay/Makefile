GCC = gcc
LIBS = -ltelebot -lpthread
INCLUDES = -Iinc -Iinc/ed_crypto
CFLAGS = $(INCLUDES) -g -Wall -Werror -o homekeeper-relay
SRCS = src/*.c src/ed_crypto/*.c

.PHONY: build

all: build

build:
	$(GCC) $(SRCS) $(CFLAGS) $(LIBS)

clean:
	rm ./homekeeper-relay
GCC = gcc
LIBS = -ltelebot -lpthread
INCLUDES = -Iinc -Iinc/ed_crypto
CFLAGS = $(INCLUDES) -g -Wall -Werror -o homekeeper-relay
SRCS = src/*.c src/ed_crypto/*.c

.PHONY: build

all: build

build:
	$(GCC) $(SRCS) $(CFLAGS) $(LIBS)

install:
	mv homekeeper-relay /usr/local/bin/homekeeper-relay
	yes | cp -rf /service/homekeeper-relay.service /etc/systemd/system/homekeeper-relay.service
	systemctl start homekeeper-relay
	systemctl enable homekeeper-relay

clean:
	rm ./homekeeper-relay
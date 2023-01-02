GNULIBS = -ltelebot
CFLAGS = -Wall -Werror

.PHONY:
	build

build:
	cc -o main main.c $(CFLAGS) $(GNULIBS)

clean:
	rm ./main
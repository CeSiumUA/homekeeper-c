GNULIBS = -ltelebot
CFLAGS = -Wall -Werror

build:
	cc -o main main.c $(CFLAGS) $(GNULIBS)

clean:
	rm ./main
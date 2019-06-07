CC = gcc
CFLAGS = -g
SOURCES = $(wildcard *.c)
BINAIRES = $(patsubst %.c,%.o,${SOURCES})

main : ${BINAIRES}
	${CC} ${CFLAGS} -o $@ $^ -lwiringPi -lm -lpthread

clean :
	rm -f main
	rm -f *.o

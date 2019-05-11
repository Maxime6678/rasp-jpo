CC = gcc
CFLAGS = -g
SOURCES = $(wildcard *.c)
BINAIRES = $(patsubst %.c,%.o,${SOURCES})

main : ${BINAIRES}
	${CC} ${CFLAGS} -o $@ $^

clean :
	rm -f main
	rm -f *.o

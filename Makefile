CC=gcc
LFLAGS=
CFLAGS=-pedantic -ansi -W -Wextra

cmap: main.o bmap.o
	$(CC) -o cmap $^ $(LFLAGS)

main.o: main.c bmap.h
	$(CC) -c $^ $(CFLAGS)

bmap.o: bmap.c bmap.h
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *.o cmap


CFLAGS=-pedantic -ansi -W -Wextra

cmap: main.o bmap.o
	$(CC) -o cmap $^ $(LFLAGS)

%.o: %.c bmap.h

clean:
	rm -f *.o cmap


FLAGC=-c
FLAGO=-o


all: memgrind

mymalloc.o: mymalloc.c mymalloc.h
	gcc $(FLAGC) mymalloc.c

memgrind: mymalloc.o memgrind.c
	gcc $(FLAGO) memgrind memgrind.c mymalloc.o

clean:
	rm -f mymalloc.o memgrind

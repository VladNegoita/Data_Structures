#Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=linkedlist

#define dependencies
DEPS=linkedlist.h utils.h

#define object-files
OBJ=linkedlist.o main.o

build: $(TARGETS)

linkedlist: $(OBJ)
	$(CC) $(CFLAGS) *.o -o linkedlist

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr 311CA_VladNegoita_TemaPCLP3.zip Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
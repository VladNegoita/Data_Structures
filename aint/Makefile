#Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=aint_exec

#define dependencies
DEPS=aint.h

#define object-files
OBJ=aint.o main.o

build: $(TARGETS)

aint_exec: $(OBJ)
	$(CC) $(CFLAGS) *.o -o aint_exec

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

pack:
	zip -FSr 311CA_VladNegoita_TemaPCLP3.zip Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
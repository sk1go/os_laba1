CC=gcc
CFLAGS=-O2 -Wall -W -pedantic

all: testavl

testavl:
$(CC) testavl.c avltree.c -o testavl CFLAGS


clean:
@rm testavl

.PHONY: clean
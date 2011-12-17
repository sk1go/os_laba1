CC=gcc
CFLAGS=-O2 -Wall -W -pedantic

all: testavl

testavl:
$(CC) test_avl.c avltree.c -o test_avl CFLAGS


clean:
@rm test_avl

.PHONY: clean
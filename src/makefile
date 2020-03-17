CC=clang
CFLAGS=-Wall -Wextra -Wno-char-subscripts

all:

clean:
	rm -f C test_literal test_clause *.o

literal.o: literal.c literal.h
	$(CC) $(CFLAGS) -c literal.c

clause.o: clause.c clause.h literal.h
	$(CC) $(CFLAGS) -c clause.c

tests: test_literal test_clause

test_literal: test_literal.o literal.o
	$(CC) $(CFLAGS) -o test_literal test_literal.o literal.o

test_literal.o: test_literal.c literal.h
	$(CC) $(CFLAGS) -c test_literal.c

test_clause: test_clause.o clause.o literal.o
	$(CC) $(CFLAGS) -o test_clause test_clause.o clause.o literal.o

test_clause.o: test_clause.c clause.h literal.h
	$(CC) $(CFLAGS) -c test_clause.c

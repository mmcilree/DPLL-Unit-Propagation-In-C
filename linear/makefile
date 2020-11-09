CC=clang
CFLAGS=-Wall -Wextra -Wno-char-subscripts

all: main

main: main.o linearpropagator.o parser.o formula.o clause.o literal.o
	$(CC) $(CFLAGS) -o main main.o linearpropagator.o parser.o formula.o clause.o literal.o

clean:
	rm -f main test_literal test_clause test_formula *.o

literal.o: literal.c literal.h clause.h formula.h
	$(CC) $(CFLAGS) -c literal.c

clause.o: clause.c clause.h literal.h
	$(CC) $(CFLAGS) -c clause.c

formula.o: formula.c clause.h
	$(CC) $(CFLAGS) -c formula.c

parser.o: parser.c parser.h formula.h clause.h literal.h
	$(CC) $(CFLAGS) -c parser.c

linearpropagator.o: linearpropagator.c linearpropagator.h formula.h clause.h literal.h
	$(CC) $(CFLAGS) -c linearpropagator.c

main.o: main.c linearpropagator.h parser.h formula.h literal.h clause.h
	$(CC) $(CFLAGS) -c main.c


tests: test_literal test_clause test_formula

test_literal: test_literal.o literal.o
	$(CC) $(CFLAGS) -o test_literal test_literal.o literal.o

test_literal.o: test_literal.c literal.h
	$(CC) $(CFLAGS) -c test_literal.c

test_clause: test_clause.o clause.o literal.o
	$(CC) $(CFLAGS) -o test_clause test_clause.o clause.o literal.o

test_clause.o: test_clause.c clause.h literal.h
	$(CC) $(CFLAGS) -c test_clause.c

test_formula: test_formula.o formula.o clause.o literal.o
	$(CC) $(CFLAGS) -o test_formula test_formula.o formula.o clause.o literal.o

test_formula.o: test_formula.c formula.h clause.h literal.h
	$(CC) $(CFLAGS) -c test_formula.c

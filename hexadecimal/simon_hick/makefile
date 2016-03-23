CC = gcc
CFLAGS = -Wall -Werror

tests: student_code.o tests.o
	$(CC) -o tests student_code.o tests.o $(CFLAGS) -lcunit

student_code.o: student_code.c student_code.h
	$(CC) -c student_code.c  $(CFLAGS)

tests.o: tests.c student_code.h
	$(CC) -c tests.c $(CFLAGS) -lcunit 

.PHONY: clean

clean: 
	rm -rf *.o tests

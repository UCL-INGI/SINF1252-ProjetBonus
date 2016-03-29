CC = gcc
FLAG = -lcunit


all: student_code clean

student_code: student_code.o tests.o
	@$(CC) -o student_code student_code.o tests.o $(FLAG)
	@./student_code

student_code.o: student_code.c student_code.h
	@$(CC) -c student_code.c -o student_code.o

tests.o: tests.c student_code.h
	@$(CC) -c tests.c -o tests.o $(FLAG)

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf student_code

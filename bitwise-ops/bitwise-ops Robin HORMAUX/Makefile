student_code: student_code.o tests.o
	gcc -I$(HOME)/local/include -L$(HOME)/local/lib student_code.o tests.o -o student_code -lcunit

student_code.o: student_code.c student_code_HORMAUX.h
	gcc -c student_code.c

tests.o: tests.c student_code.h
	gcc -I$(HOME)/local/include tests.c -L$(HOME)/local/lib tests.c -lcunit -c -lcunit

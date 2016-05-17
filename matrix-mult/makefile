matrix_mult : student_code.o tests.c
	gcc tests.c -I$(HOME)/local/include -L$(HOME)/local/lib student_code.o -lcunit -o matrix_mult
student_code.o : student_code.c
	gcc -c student_code.c

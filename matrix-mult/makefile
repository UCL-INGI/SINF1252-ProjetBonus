matrix-mult : student_code.o tests.c
	gcc tests.c -I$(HOME)/local/include -L$(HOME)/local/lib student_code.o -lcunit -o matrix-mult
matrix-mult.o : student_code.c student_code.h
	gcc -c student_code.c
clean :
	rm -f *.o

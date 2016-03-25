all: exec
exec: Polo
		./Polo
Polo: student_code.o tests.o
		gcc -o Polo student_code.o tests.o -I$(HOME)/local/include -L$(HOME)/local/lib -lcunit
student_code.o: student_code.c student_code.h
		gcc  -c student_code.c -W -Wall
tests.o: tests.c student_code.h
		gcc  -c tests.c -I$(HOME)/local/include -L$(HOME)/local/lib -lcunit -W -Wall
clean:
	rm -f *.o
.PHONY: all exec
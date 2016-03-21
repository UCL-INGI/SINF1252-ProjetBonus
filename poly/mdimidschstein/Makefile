tests : student_code.o tests.o
	gcc -o tests -I$(HOME)/local/include -L$(HOME)/local/lib tests.o student_code.o -lcunit
	
student_code.o : student_code.c student_code.h
	gcc -c student_code.c 

tests.o : tests.c student_code.h
	gcc -Wall -c tests.c -I$(HOME)/local/include -L$(HOME)/local/lib -lcunit
	    
clean :
	rm -f *.o tests
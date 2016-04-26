
all:
	gcc -D C99 -fPIC -shared -o myfonctions.so myfonctions.c -ldl -pthread
	gcc -D C99 student_code.c tests.c -lcunit -rdynamic -o tests -pthread

run:
	LD_PRELOAD=./myfonctions.so ./tests

.PHONY: run

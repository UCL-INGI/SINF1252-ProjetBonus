
all:
	gcc -D C99 -fPIC -shared -o myfunctions.so myfunctions.c -ldl -pthread
	gcc -D C99 student_code.c tests.c -lcunit -rdynamic -o tests -pthread

run:
	LD_PRELOAD=./myfunctions.so ./tests

.PHONY: run

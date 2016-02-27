all:
	gcc -Wall -Werror -fPIC -shared -o mymalloc.so mymalloc.c -ldl
	gcc -Wall -Werror student_code.c tests.c -lcunit -rdynamic -o tests

run:
	LD_PRELOAD=./mymalloc.so ./tests

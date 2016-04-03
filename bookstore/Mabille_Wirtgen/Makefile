all:
	gcc -Wall -Werror -fPIC -shared -o myfree.so myfree.c -ldl
	gcc -Wall -Werror student_code.c tests.c -lcunit -rdynamic -o tests

.PHONY: run

run:
	LD_PRELOAD=./myfree.so ./tests

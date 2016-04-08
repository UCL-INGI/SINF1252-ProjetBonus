all: 
	gcc -D C99 -Wall -Werror -fPIC -shared -o mymalloc.so mymalloc.c -ldl
	gcc -D C99 -Wall -Werror -fPIC -shared -o myfree.so myfree.c -ldl
	gcc -D C99 -Wall -Werror student_code.c tests.c -lcunit -rdynamic -o tests
	
run:
	LD_PRELOAD=./mymalloc.so ./myfree.so ./tests

.PHONY: run

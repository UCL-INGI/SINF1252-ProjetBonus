all: 
	gcc -D C99 -std=gnu99 -Wall -Werror -fPIC -shared -o mydestroy.so mydestroy.c -ldl -g
	gcc -pthread -D C99 -std=gnu99 -Wall -Werror student_code.c tests.c -lcunit -rdynamic -o tests -g
	
run:
	LD_PRELOAD=./mydestroy.so ./tests

.PHONY: run

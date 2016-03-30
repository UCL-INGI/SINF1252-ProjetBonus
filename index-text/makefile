CFLAGS = -I$(HOME)/local/include 
LDFLAGS = -L$(HOME)/local/lib -lcunit

all:
	gcc -D C99 -Wall -Werror -fPIC -shared -o myfnc.so myfnc.c -ldl
	gcc -D C99 -Wall -Werror $(CFLAGS) student_code.c tests.c $(LDFLAGS) -rdynamic -o tests
run:
	LD_PRELOAD=./myfnc.so ./tests

.PHONY: run
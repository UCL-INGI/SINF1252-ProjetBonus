FLAGS = -Wall

tests: student_code.o tests.o
	@echo "Linking objects"
	@gcc -o tests tests.o student_code.o -L$(HOME)/local/lib -lcunit $(FLAGS)
	@echo "Launching tests"
	@./tests

tests.o: tests.c
	@echo "Creating tests object"
	@gcc -c -o tests.o tests.c -I$(HOME)/local/include $(FLAGS)

student_code.o: student_code.c
	@echo "Creating code object"
	@gcc -c -o student_code.o student_code.c $(FLAGS)

clean:
	@echo "Removing objects files"
	@rm -rf *o

mrproper: clean
	@echo "Removing exec"
	@rm tests

.PHONY: clean mrproper

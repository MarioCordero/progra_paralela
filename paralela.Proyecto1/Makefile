# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general clean
valgrind: compile_valgrind execute_valgrind clean

# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general

# Variables
INPUTFILE = prueba.txt
FILES = main.cpp
EXECUTABLE = executeme

# COMPILERS INSTANCES pthread
compile_general:
	g++ -o $(EXECUTABLE) $(FILES)

compile_valgrind:
	g++ -pthread -g -o $(EXECUTABLE) $(FILES)

compile_ThreadSanitizer:
	gcc -pthread -fsanitize=thread -o executeme calcPi_pthread03.c -lm

compile_ThreadSanitizer_clang:
	clang -pthread -fsanitize=thread -o executeme pthread02.c

clean:
	rm -f $(EXECUTABLE)

# EXECUTERS INSTANCES
execute_general:
	./$(EXECUTABLE) < $(INPUTFILE)

execute_valgrind:
	valgrind --tool=helgrind ./$(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE) < $(INPUTFILE)
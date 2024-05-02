# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general
valgrind: compile_valgrind execute_valgrind

# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general

# gcc -pthread -o executeme calcularPImsg01.c -lm
# gcc -pthread -g -o executeme calcularPImsg01.2.1.c -lm

# gcc -pthread -o executeme calcularPImsg01.2.3.c -lm
# gcc -pthread -g -o executeme calcularPImsg01.2.3.c -lm

# COMPILERS INSTANCES
compile_general:
	gcc -pthread -o executeme calcularPImsg01.2.4.c -lm

compile_valgrind:
	gcc -pthread -g -o executeme calcularPImsg01.2.4.c -lm

compile_ThreadSanitizer:
	gcc -pthread -fsanitize=thread -o executeme calcularPImsg01.c -lm

compile_ThreadSanitizer_clang:
	clang -pthread -fsanitize=thread -o executeme calcularPImsg01.c

# EXECUTERS INSTANCES
execute_general:
	./executeme $(ARGS)

execute_valgrind:
	valgrind --tool=helgrind ./executeme $(ARGS)


# The math library must be linked in when building the executable. How to do this varies by environment, but in Linux/Unix, just add -lm to the command:

# gcc test.c -o test -lm

# The math library is named libm.so, and the -l command option assumes a lib prefix and .a or .so suffix.

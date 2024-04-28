# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general
valgrind: compile_valgrind execute_valgrind
# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general

# COMPILERS INSTANCES pthread
compile_general:
	gcc -pthread -o executeme pthread03.c

compile_valgrind:
	gcc -pthread -g -o executeme pthread04argsThreads.c

compile_ThreadSanitizer:
	gcc -pthread -fsanitize=thread -o executeme pthread02.c

compile_ThreadSanitizer_clang:
	clang -pthread -fsanitize=thread -o executeme pthread02.c


# EXECUTERS INSTANCES
execute_general:
	./executeme

execute_valgrind:
	valgrind --tool=helgrind ./executeme
# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general
valgrind: compile_valgrind execute_valgrind
# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general

# gcc -pthread -o executeme calcPi.c

# gcc -pthread -o executeme calcPi_pthread01.c -lm
# gcc -pthread -g -o executeme calcPi_pthread01.c -lm

# gcc -pthread -o executeme calcPi_pthread02.c -lm
# gcc -pthread -g -o executeme calcPi_pthread02.c -lm

# gcc -pthread -o executeme calcPi_pthread03.c -lm
# gcc -pthread -g -o executeme calcPi_pthread03.c -lm

# gcc -pthread -o executeme calcPi_pthread04.c -lm
# gcc -pthread -g -o executeme calcPi_pthread04.c -lm



# COMPILERS INSTANCES pthread
compile_general:
	gcc -pthread -o executeme calcPi_pthread05.c -lm

compile_valgrind:
	gcc -pthread -g -o executeme calcPi_pthread04.c -lm

compile_ThreadSanitizer:
	gcc -pthread -fsanitize=thread -o executeme calcPi_pthread03.c -lm

compile_ThreadSanitizer_clang:
	clang -pthread -fsanitize=thread -o executeme pthread02.c


# EXECUTERS INSTANCES
execute_general:
	time ./executeme $(ARGS)

execute_valgrind:
	valgrind --tool=helgrind time ./executeme $(ARGS)
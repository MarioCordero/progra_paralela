all: compile_general execute_general
compile: compile_general

# COMPILERS INSTANCES
compile_general:
	gcc -o executeme main.c -lm -pthread

# EXECUTERS INSTANCES
execute_general:
	./executeme



# The math library must be linked in when building the executable. How to do this varies by environment, but in Linux/Unix, just add -lm to the command:

# gcc test.c -o test -lm

# The math library is named libm.so, and the -l command option assumes a lib prefix and .a or .so suffix.

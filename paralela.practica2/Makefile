# The name of the file to compile
FILE := $(word 1,$(ARGS))
# The machine language file output
BINARY = executeme

# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general clean
valgrind: compile_valgrind execute_valgrind
# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general

# COMPILERS INSTANCES pthread
compile_general:
	@echo "Compilando-ando $(FILE)..."
	@echo "\n"
	gcc -pthread -o $(BINARY) $(FILE)

compile_valgrind:
	gcc -pthread -g -o $(BINARY) $(FILE)

compile_ThreadSanitizer:
	gcc -pthread -fsanitize=thread -o $(BINARY) $(FILE)

compile_ThreadSanitizer_clang:
	clang -pthread -fsanitize=thread -o $(BINARY) $(FILE)

# EXECUTERS INSTANCES
execute_general:
	./$(BINARY)

clean:
	@echo "\n"
	@echo "Limpiando archivos compilados..."
	rm -f $(BINARY)

execute_valgrind:
	valgrind --tool=helgrind ./$(BINARY)
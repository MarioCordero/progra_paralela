# Verificar si ARGS está definido
ifndef ARGS
$(error No se proporcionaron argumentos. Ejecute con make ARGS="nombre del archivo")
endif

# The name of the file to compile
FILE := $(word 1,$(ARGS))
# The machine language file output
BINARY = executeme

# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general clean
disassemble: compile_general execute_general disassemble
valgrind: compile_valgrind execute_valgrind disassemble clean

# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general disassemble clean
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general disassemble clean


# Variables
OBJDUMP = objdump -d
EXECUTABLE = executeme

# COMPILERS INSTANCES pthread
compile_general:
	gcc -o $(EXECUTABLE) -msse4.1 $(FILES)

compile_valgrind:
	g++ -pthread -g -o $(EXECUTABLE)

compile_ThreadSanitizer:
	gcc -pthread -fsanitize=thread -o $(EXECUTABLE) $(FILES) -lm

compile_ThreadSanitizer_clang:
	clang -pthread -fsanitize=thread -o $(EXECUTABLE) $(FILES)

clean:
	@echo "\n"
	@echo "Limpiando archivos compilados..."
	rm -f $(BINARY)

# EXECUTERS INSTANCES
execute_general:
	@echo "\n"
	./$(EXECUTABLE)
	@echo "\n"

execute_valgrind:
	valgrind --tool=helgrind ./$(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)

# Disassemble the executable
disassemble:
	$(OBJDUMP) $(EXECUTABLE)

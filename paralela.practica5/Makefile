# Verificar si ARGS está definido
ifndef ARGS
$(error No se proporcionaron argumentos. Ejecute con make ARGS="nombre del archivo")
endif

# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general clean
disassemble: compile_general execute_general disassemble
valgrind: compile_valgrind execute_valgrind disassemble clean

# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general disassemble clean
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general disassemble clean


# Variables
OBJDUMP = objdump -d
INPUTFILE = prueba.txt
FILES = $(ARGS)
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
	rm -f $(EXECUTABLE)

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

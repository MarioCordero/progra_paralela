# Verificar si ARGS está definido
ifndef ARGS
$(error No se proporcionaron argumentos. Ejecute con make ARGS="nombre del archivo")
endif

# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general clean


# Variables
OBJDUMP = objdump -d
INPUTFILE = prueba.txt
FILES = $(ARGS)
EXECUTABLE = executeme

# COMPILERS INSTANCES pthread
compile_general:
	gcc -o $(EXECUTABLE) -msse4.1 $(FILES)

compile_general_cuda:
	nvcc add.cu -o add_cuda

clean:
	@echo "\n"
	rm -f $(EXECUTABLE)

# EXECUTERS INSTANCES
execute_general:
	@echo "\n"
	./$(EXECUTABLE)
	@echo "\n"
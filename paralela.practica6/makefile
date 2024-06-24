# Verificar si ARGS está definido
# ifndef ARGS
# $(error No se proporcionaron argumentos. Ejecute con make ARGS="nombre del archivo")
# endif

# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: errMSG
c++: compile_c++ execute_general clean
CUDA: compile_CUDA execute_general clean


# Variables
C++EXAMPLE = ejemplo1.cpp
CUDAEXAMPLE = ejemplo2.cu

EXECUTABLE = executeme

errMSG:
	@echo "\n"
	$(error Asi no se usa esto, revise la documentacion porfa.")
	@echo "\n"

# COMPILERS INSTANCES pthread
compile_c++:
	g++ -o $(EXECUTABLE) $(C++EXAMPLE)

compile_CUDA:
	nvcc -o $(EXECUTABLE) $(CUDAEXAMPLE)

clean:
	@echo "\n"
	rm -f $(EXECUTABLE)

# EXECUTERS INSTANCES
execute_general:
	@echo "\n"
	./$(EXECUTABLE)
	@echo "\n"
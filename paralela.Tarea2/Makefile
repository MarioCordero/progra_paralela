# Verifying the ARGS
ifndef ARGS

$(info )
$(info )
$(error No se proporcionaron argumentos necesarios. Ejecute con make ARGS="[archivo] [#puntos] [#hilos]")

endif

# The number of args
NUM_ARGS := $(words $(ARGS))

# Verifying if the input has the 3 args
ifeq ($(NUM_ARGS), 0)
$(info )
$(info )
$(error No se proporcionaron argumentos necesarios. Ejecute con make ARGS="[archivo] [#puntos] [#hilos]")
endif

ifeq ($(NUM_ARGS), 1)
$(info )
$(info )
$(error No se proporcionaron argumentos necesarios. Ejecute con make ARGS="[archivo] [#puntos] [#hilos]")
endif

ifeq ($(NUM_ARGS), 2)
$(info )
$(info )
$(error No se proporcionaron argumentos necesarios. Ejecute con make ARGS="[archivo] [#puntos] [#hilos]")
endif


# NOTE: REMEMBER INSTALL GCC VALGRIND CLANG
all: compile_general execute_general clean
valgrind: compile_valgrind execute_valgrind

# NOTE: Do not use ThreadSanitizer in big programs or in production
ThreadSanitizer: compile_ThreadSanitizer execute_general
ThreadSanitizer-clang: compile_ThreadSanitizer_clang execute_general

# The name of the file to compile
FILE := $(word 1,$(ARGS))
POINTS := $(word 2,$(ARGS))
THREADS := $(word 3,$(ARGS))
# The machine language file output
BINARY = executeme

# gcc -pthread -o executeme calcularPImsg01.c -lm
# gcc -pthread -g -o executeme calcularPImsg01.2.1.c -lm

# gcc -pthread -o executeme calcularPImsg01.2.3.c -lm
# gcc -pthread -g -o executeme calcularPImsg01.2.3.c -lm

# COMPILERS INSTANCES
compile_general:
	@echo "Compilando-ando $(FILE)..."
	@echo "\n"
	gcc -pthread -o $(BINARY) $(FILE) -lm

compile_valgrind:
	gcc -pthread -g -o executeme calcularPImsg01.2.4.c -lm

compile_ThreadSanitizer:
	gcc -pthread -fsanitize=thread -o executeme calcularPImsg01.c -lm

compile_ThreadSanitizer_clang:
	clang -pthread -fsanitize=thread -o executeme calcularPImsg01.c

# EXECUTERS INSTANCES
execute_general:
	./$(BINARY) $(POINTS) $(THREADS)

execute_valgrind:
	valgrind --tool=helgrind ./executeme $(ARGS)

clean:
	@echo "\n"
	@echo "Limpiando archivos compilados..."
	rm -f $(BINARY)
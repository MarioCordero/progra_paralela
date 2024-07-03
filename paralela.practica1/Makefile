all: compile_general execute_general clean

# The name of the file to compile
FILE := $(word 1,$(ARGS))
# The machine language file output
BINARY = executeme

compile_general:
	@echo "Compilando-ando $(FILE)..."
	@echo "\n"
	gcc -pthread -o $(BINARY) $(FILE) -lm

# EXECUTERS INSTANCES
execute_general:
	./$(BINARY)

clean:
	@echo "\n"
	@echo "Limpiando archivos compilados..."
	rm -f $(BINARY)
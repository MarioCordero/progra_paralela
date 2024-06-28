# Makefile para el programa hello.go

# Variables
GOFILES = problemaFumadores.go
BINARY = problemaFumadores

all: build run clean

build:
	@echo "Compilando el programa..."
	@echo "\n"
	go build -o $(BINARY) $(GOFILES)

run: build
	@echo "Ejecutando el programa..."
	@echo "\n"
	./$(BINARY)

clean:
	@echo "\n"
	@echo "Limpiando archivos compilados..."
	rm -f $(BINARY)
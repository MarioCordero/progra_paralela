# Makefile para el programa hello.go

# Variables
GOFILES = problemaFumadores.go
BINARY = problemaFumadores

# Reglas
.PHONY: all clean run

all: build run clean

build:
	@echo "Compilando el programa..."
	go build -o $(BINARY) $(GOFILES)

run: build
	@echo "Ejecutando el programa..."
	./$(BINARY)

clean:
	@echo "Limpiando archivos compilados..."
	rm -f $(BINARY)
BIN=./bin
SRC=./src
OBJ=./obj
DATA=./data
INC=./include
TEX=./tex
FLAGS=-std=c++11 -lm -c -I $(INC)

# make all: Compilar todos los programas
all: main

main: $(patsubst $(SRC)/%.cc, $(OBJ)/%.o, $(wildcard $(SRC)/*.cc))
	g++ $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.cc
	g++ $< -o $@ $(FLAGS)

# Limpieza de los ejecutables
clean:
	rm $(BIN)/* $(OBJ)/*

.PHONY: clean

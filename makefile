BIN=./bin
SRC=./src
OBJ=./obj
DATA=./data
INC=./include
TEX=./tex
FLAGS=-std=c++11 -lm -c -I $(INC)

# make all: Compilar todos los programas
all: main

main: $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/*.cpp))
	g++ $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.cpp
	g++ $< -o $@ $(FLAGS)

# Limpieza de los ejecutables
clean:
	rm $(BIN)/* $(OBJ)/*

.PHONY: clean

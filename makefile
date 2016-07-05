BIN=./bin
SRC=./src
OBJ=./obj
DATA=./data
PLOT=./plots
FIT=./regressionPlots
TEX=./tex
FLAGS=-std=c++0x -Wall -lm -c

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

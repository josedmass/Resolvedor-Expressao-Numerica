CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/ArvoreBinaria.o $(OBJ)/Expressao.o $(OBJ)/operacoes.o $(OBJ)/PilhaEncadeada.o 
HDRS = $(INC)/ArvoreBinaria.h $(INC)/Expressao.h $(INC)/operacoes.h $(INC)/PilhaEncadeada.h $(INC)/Excecoes.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run: $(EXE)
	./$(EXE) $(filter-out $@,$(MAKECMDGOALS))

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/ArvoreBinaria.o: $(HDRS) $(SRC)/ArvoreBinaria.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/ArvoreBinaria.o $(SRC)/ArvoreBinaria.cpp

$(OBJ)/Expressao.o: $(HDRS) $(SRC)/Expressao.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Expressao.o $(SRC)/Expressao.cpp

$(OBJ)/operacoes.o: $(HDRS) $(SRC)/operacoes.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/operacoes.o $(SRC)/operacoes.cpp

$(OBJ)/PilhaEncadeada.o: $(HDRS) $(SRC)/PilhaEncadeada.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/PilhaEncadeada.o $(SRC)/PilhaEncadeada.cpp
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
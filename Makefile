COMP = gcc
FLAGS = -std=c99 -g3 -Wall
SRC = *.c
OBJ = *.o
BIN = HostsMod

$(BIN) : $(OBJ)
	$(COMP) $(FLAGS) $(OBJ) -o $(BIN)
	rm $(OBJ)
$(OBJ) : $(SRC)
	$(COMP) $(FLAGS) -c $(SRC)
clean : 
	rm $(BIN) $(OBJ)


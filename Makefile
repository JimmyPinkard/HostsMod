COMP = gcc
FLAGS = -std=c99 -g3 -Wall
SRC = *.c
OBJ = *.o
DEPS = header.h
BIN = HostsMod

$(BIN) : $(OBJ)
	$(COMP) $(FLAGS) $(OBJ) -o $(BIN)
	rm $(OBJ)
$(OBJ) : $(SRC) $(DEPS)
	$(COMP) $(FLAGS) -c $(SRC)
clean :
	rm $(OBJ)
windows :
	$(COMP) main.c -o $(BIN)

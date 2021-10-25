FLAGS = -std=c99 -g3 -Wall
SRC = *.c
OBJ = *.o
DEPS = header.h
BIN = HostsMod

$(BIN) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(BIN)
	rm $(OBJ)
$(OBJ) : $(SRC) $(DEPS)
	$(CC) $(FLAGS) -c $(SRC)
clean :
	rm $(OBJ)
windows :
	$(CC) main.c -o $(BIN)

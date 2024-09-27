CC=cc
SRC= main.c
OBJ= flower

install:
	$(CC) $(SRC) -o $(OBJ)
clean:
	rm $(OBJ)

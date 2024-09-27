CC=cc
SRC= main.c parsing.c
HEADER= parsing.h
OBJ= flower

install:
	$(CC) $(SRC) $(HEADER) -o $(OBJ)
clean:
	rm $(OBJ)

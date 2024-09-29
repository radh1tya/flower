CC=cc
SRC= main.c parsing.c
HEADER= parsing.h
OBJ= flower
FLAG= -Wall -Wextra -pedantic
install:
	$(CC) $(SRC) $(HEADER)  -o $(OBJ)
clean:
	rm $(OBJ)

# Compiler option
CC     = cc
FLAG   = -Os -Wall -Werror -Wextra -Wpedantic \
		 -std=gnu2x -Wunreachable-code \
		 -Wconversion
UNLINK = -c

# File
SRC    = main.c parsing.c
OUT    = main.o parsing.o
HEADER = parsing.h
OBJ    = flower

# make install
install:
	# $(CC) $(SRC) $(HEADER)  -o $(OBJ)
	$(CC) $(SRC) $(FLAG) $(UNLINK)
	$(CC) $(OUT) $(FLAG) -o $(OBJ)

# make clean
clean:
	rm $(OUT) $(OBJ)

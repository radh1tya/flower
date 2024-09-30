# Compiler option
CC     = cc
FLAG   = -Os -Wall -Werror -Wextra -Wpedantic \
		 -std=gnu2x -Wunreachable-code \
		 -Wconversion
UNLINK = -c

# File
SRC    = src/*.c
OUT    = *.o
OBJ    = flower

# make install
install:
	$(CC) $(SRC) $(FLAG) $(UNLINK)
	$(CC) $(OUT) $(FLAG) -o $(OBJ)

# make clean
clean:
	rm $(OUT) $(OBJ)

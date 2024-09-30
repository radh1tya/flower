# Compiler option
CC     = cc
FLAG   = -O3 -Wall -Werror -Wextra -Wpedantic \
		 -std=gnu23 -Wunreachable-code -Wc23-extensions \
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

# Compiler option
CC     = cc
FLAG   = -O3 -Wall -Werror -Wextra -Wpedantic \
		 -std=gnu23 -Wunreachable-code -Wc23-extensions \
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

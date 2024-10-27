# Compiler option
CC     = cc
FLAG   = -O3 -Wall -Werror -Wextra -Wpedantic \
		 -std=gnu99 -Wunreachable-code
UNLINK = -c

# ELF Symbols remover
# using llvm-objcopy for LLVM
# using objcopy for GNU/Binutils
STRIPPER = objcopy
LLVM-STRIPPER = llvm-$(STRIPPER)
STRIP-OPTION = --strip-unneeded

# ELF Reader
READELF	= readelf
LLVM-READELF = llvm-$(READELF)
READ-OPTION	= -hS

# Disassembler
OBJDUMP = objdump
LLVM-OBJDUMP = llvm-$(OBJDUMP)
OBJDUMP-OPTION = --disassemble

# File
SRC = src/*.c
OUT = *.o
OBJ = flower

# make install
install:
	$(CC) $(SRC) $(FLAG) $(UNLINK)
	$(CC) $(OUT) $(FLAG) -o $(OBJ)

# make debug
debug:
	$(CC) $(SRC) $(UNLINK)
	$(CC) $(OUT) -o $(OBJ)

# make run
run: $(OBJ)
	./$(OBJ)

# make gnu-strip
gnu-strip: $(OBJ)
	$(STRIPPER) $(STRIP-OPTION) $(OBJ)

# make llvm-strip
llvm-strip: $(OBJ)
	$(LLVM-STRIPPER) $(STRIP-OPTION) $(OBJ)

# make gnu-readelf
gnu-readelf: $(OBJ)
	$(READELF) $(READ-OPTION) $(OBJ)

# make llvm-readelf
llvm-readelf: $(OBJ)
	$(LLVM-READELF) $(READ-OPTION) $(OBJ)

# make gnu-objdump
gnu-objdump: $(OBJ)
	$(OBJDUMP) $(OBJDUMP-OPTION) $(OBJ)

# make llvm-objdump
llvm-objdump: $(OBJ)
	$(LLVM-OBJDUMP) $(OBJDUMP-OPTION) $(OBJ)

# make clean
clean: $(OUT) $(OBJ)
	rm $(OUT) $(OBJ)

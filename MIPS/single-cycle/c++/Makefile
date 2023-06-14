CC = g++
CFLAGS=-I -g

_DEPS = main/main.hpp main/cmd_args.hpp simulator/program_memory.hpp utils/elf_parser.hpp
_OBJ = main/main.o main/cmd_args.o simulator/program_memory.o utils/elf_parser.o

IDIR = inc
ODIR = src
EDIR = bin
OUT = mips-emul

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm $(OBJ)

.PHONY: clean
clean:
	rm $(EDIR)/$(OUT)	



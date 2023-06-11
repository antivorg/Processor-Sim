CC = g++
CFLAGS=-I -Wall

_DEPS = main/main.hpp main/cmd_args.hpp
_OBJ = main/main.o main/cmd_args.o

IDIR = inc
ODIR = src
EDIR = bin
OUT = draw

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


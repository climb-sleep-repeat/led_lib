IDIR = inc
SDIR = src
ODIR = obj
LDIR = lib

CC = gcc # C compiler

CFLAGS = -fPIC -Wall -I$(IDIR) # C flags
LDFLAGS = -shared  # linking flags
TARGET_LIB = led.so

_OBJ = i2cmodel.o led.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all
all: $(LDIR)/$(TARGET_LIB)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(LDIR)/$(TARGET_LIB): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)	

.PHONY: clean
clean:
	rm -f $(LDIR)/*.so $(ODIR)/*.o $(IDIR)/*~ $(SDIR)/*~ *~ *#

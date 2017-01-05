IDIR = inc
SDIR = src
ODIR = obj
LDIR = lib

CFLAGS = -std=c99 -fPIC -Wall -I$(IDIR) # C flags
LDFLAGS = -shared  # linking flags
TARGET_LIB = libled.so

_OBJ = i2cmodel.o led.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all
all: $(LDIR)/$(TARGET_LIB)

$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c -o $@ $< $(CFLAGS)

$(LDIR)/$(TARGET_LIB): $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) $(CFLAGS)	

.PHONY: clean
clean:
	rm -f $(LDIR)/*.so $(ODIR)/*.o $(IDIR)/*~ $(SDIR)/*~ *~ *#

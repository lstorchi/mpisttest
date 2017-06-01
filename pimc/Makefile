CC = mpicc
CFLAGS = -W -Wall 

PRGNAME = pimc

OBJ = pimc.o \
      sequential.o

all: $(PRGNAME) 

$(PRGNAME) : $(OBJ)
	$(CC) -o $@ $(OBJ) -lm

clean:
	rm -f $(OBJ) $(PRGNAME) core*

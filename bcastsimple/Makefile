CC = mpicc
CFLAGS = -W -Wall 

PRGNAME = bcast

OBJ = main.o

all: $(PRGNAME) $(PRGNAME2)

$(PRGNAME) : $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(PRGNAME) core*

CC = mpicc
CFLAGS = -W -Wall 

PRGNAME = bcast

OBJ = main.o \
	bcast.o

all: $(PRGNAME) $(PRGNAME2)

$(PRGNAME) : $(OBJ)
	$(CC) -o $@ $(OBJ) -lm

clean:
	rm -f $(OBJ) $(PRGNAME) core*

main.o: funcinc.h
bcast.o: funcinc.h

CC = mpicc
CFLAGS = -g -O0
LD = mpicc
LDFLAGS = -g

PROGRAM = hello_mpi

all : ${PROGRAM}

${PROGRAM}+: ${PROGRAM}.o
	${LD} ${LDFLAGS} $< -o ${PROGRAM}

${PROGRAM}.o: ${PROGRAM}.c
	${CC} ${CFLAGS} -c $< -o ${PROGRAM}.o

clean:
	rm -f ${PROGRAM}.o ${PROGRAM}

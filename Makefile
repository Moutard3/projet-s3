CC=gcc
CFLAGS=-W -Wall -ansi
EXEC=scrutins
SRC=src
DIST=build/make
TMP=tmp

all: ${EXEC}

scrutins: main.o
	${CC} -o ${DIST}/scrutins ${TMP}/main.o ${SRC}/global.h ${TMP}/elementliste.o ${TMP}/circuit.o ${TMP}/condorcet.o ${TMP}/liste.o ${TMP}/utils_sd.o ${TMP}/uninomiales.o

main.o: ${SRC}/main.c ${SRC}/global.h liste.o utils_sd.o uninomiales.o condorcet.o circuit.o
	${CC} -o ${TMP}/main.o -c ${SRC}/main.c

circuit.o: ${SRC}/circuit.c ${SRC}/circuit.h
	${CC} -o ${TMP}/circuit.o -c ${SRC}/circuit.c

condorcet.o: ${SRC}/condorcet.c ${SRC}/condorcet.h circuit.o
	${CC} -o ${TMP}/condorcet.o -c ${SRC}/condorcet.c

elementliste.o: ${SRC}/elementliste.c ${SRC}/elementliste.h
	${CC} -o ${TMP}/elementliste.o -c ${SRC}/elementliste.c

liste.o: ${SRC}/liste.c ${SRC}/liste.h elementliste.o
	${CC} -o ${TMP}/liste.o -c ${SRC}/liste.c

uninomiales.o: ${SRC}/uninomiales.c ${SRC}/uninomiales.h
	${CC} -o ${TMP}/uninomiales.o -c ${SRC}/uninomiales.c

utils_sd.o: ${SRC}/utils_sd.c ${SRC}/utils_sd.h
	${CC} -o ${TMP}/utils_sd.o -c ${SRC}/utils_sd.c

clean:
	rm -rf {TMP}/*
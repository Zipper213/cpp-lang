CC = g++
CFLAGS = -g
SRC := ${wildcard src/*.cpp}
HDR := ${wildcard include/*.h}
EXEC = pl

FILE = ""
GRAMMAR = ""

all:
	${CC} ${CFLAGS} ${SRC} -o ${EXEC}.exe
rm:
	del ${EXEC}.exe
run:
	${EXEC}.exe compile ${FILE} ${GRAMMAR}

DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = ${wildcard ${DIR_SRC}/*.cpp}
OBJ = ${patsubst %.cpp,${DIR_OBJ}/%.o,${notdir ${SRC}}}

TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++

LFLAGS = -lboost_system -lboost_serialization

CFLAGS = -g -std=c++11 -Wall -Wno-unused-variable -I${DIR_INC}

${BIN_TARGET}: ${OBJ}
	${CC} ${OBJ} -o ${BIN_TARGET} ${LFLAGS}

${DIR_OBJ}/%.o: ${DIR_SRC}/%.cpp
	${CC} ${CFLAGS} -c $< -o $@

.PHONY:clean
clean:
	rm ${DIR_OBJ}/*.o ${DIR_BIN}/*

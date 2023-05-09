.SILENT: all
.PHONY:  all

CC = gcc
SRC = $(shell find -name '*.c')
BIN = main
OPT = -O3 -march=native

all: 
	${CC} ${SRC} -o ${BIN} ${OPT}


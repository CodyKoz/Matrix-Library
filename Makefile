CC=gcc
CFlags=-Wall

SRCS=Matrix_Library.c
OBJS=$(SRCS: .c=.o)
EXEC=Matrix_Library

all: $(EXEC)




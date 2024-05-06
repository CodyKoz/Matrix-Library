CC=gcc
CFLAGS=-Wall 

SRCS=src/Matrix_Library.c Tests/Test_Library.c
OBJS=$(SRCS:.c=.o)
EXEC=Matrix-Library

all: build

build: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(EXEC)

run: build
	./$(EXEC)
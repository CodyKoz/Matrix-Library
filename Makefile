CC=gcc
CFLAGS=-Wall

SRCS=Tests/Test_Library.c src/Matrix_Library.c
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
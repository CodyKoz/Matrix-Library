CC=gcc
CFlags=-Wall # update CFLAGS to all caps

SRCS=src/Matrix_Library.c Tests/Test_Library.c
OBJS=$(SRCS:.c=.o)
EXEC=Matrix-Library

all: build

build: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFlags) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFlags) -c $< -o $@

clean:
	rm -rf $(OBJS) $(EXEC)

run: build
	./$(EXEC)
CC=gcc
CFlags=-Wall

SRCS=Matrix_Library.c
OBJS=$(SRCS: .c=.o)
EXEC=Matrix_Library

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFlags) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFlags) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

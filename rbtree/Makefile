CC=gcc
CFLAG=-std=c99 -Wall -Wextra -m64 -pipe -g
EXEC=rbtree

#=======================================

all: build

build: $(EXEC)

run: $(EXEC)
	./$(EXEC)

memchk: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

$(EXEC): main.o rbtree.o
	$(CC) $(CFLAG) -o $@ $^

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

.PHONY: style
style:
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.[ch]

.PHONY: clean
clean:
	rm *.o $(EXEC)

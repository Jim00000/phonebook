CC=gcc
CFLAG=-std=gnu99 -Wall -Wextra -O0
EXEC= hash

all: $(EXEC)

hash: main.o 
	$(CC) $(CFLAG) -o $@ main.o

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

run: $(EXEC)
	watch -d -t ./$(EXEC)

style: 
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.[ch]

.PHONY: clean
clean:
	rm $(EXEC) *.o

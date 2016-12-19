CC=gcc
CFLAG=-std=gnu99 -m64 -pipe -Wall -Wextra -O0 
DEBUG=
EXEC=fuzzysearch
OBJ=fuzzy_search.o main.o
#============================================

all: default

default: $(EXEC)


run: $(EXEC)
	./$(EXEC)

debug: clean debug-flag $(EXEC)   
	
debug-flag:
	$(eval DEBUG +=-g)

$(EXEC): $(OBJ)
	$(CC) $(CFLAG) $(DEBUG) -o $@ $^

%.o : %.c
	$(CC) $(CFLAG) $(DEBUG) -c $< -o $@

style:
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.[ch]

.PHONY:clean
clean:
	rm $(EXEC) *.o

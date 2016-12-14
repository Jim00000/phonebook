CC ?= gcc
CFLAGS_common ?= -Wall -Wextra -std=gnu99 -m64
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)

SRCS_common = main.c

DEBUG_MEMLEAK =-DMEMLEAK -g

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DOPT=1 \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

debug:
	$(eval CFLAGS_common += $(DEBUG_MEMLEAK))

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses:u,cache-references:u,instructions:u,cycles:u \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses:u,cache-references:u,instructions:u,cycles:u \
		./phonebook_opt

output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

style: 
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.[ch]

.PHONY: memcheak
memcheak: clean debug $(EXEC)
	./phonebook_orig
	mtrace memleak.log
	./phonebook_opt
	mtrace memleak.log

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png memleak.log

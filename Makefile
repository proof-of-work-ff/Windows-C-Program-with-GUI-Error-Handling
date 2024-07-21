#compiler name
CC := gcc -g -Wall `pkg-config --cflags --libs gtk+-2.0`

#remove command
RM := rm -rf

#source files
SOURCES := main.c

%.o: %.c
	$(CC) -c $< -o $@
 
#object files
OBJS := $(SOURCES:.c=.o)

#main target
main: $(OBJS)
	$(CC) $^ -o $@

run: main
	./main

.PHONY: clean
clean:
	$(RM) *.o main
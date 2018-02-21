CC=gcc
CFLAGS=-pipe -ansi -W -Wall -Wextra -Werror -Wconversion -Wpadded -pedantic -O3 -fmessage-length=0
LDFLAGS=-pipe -O3
LDLIBS=-lncurses
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXEC=prog

.PHONY: clean mrproper

all: clean depend $(EXEC)

$(EXEC):	$(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

depend:
	@makedepend -- $(CFLAGS) -- -Y $(SRC) 2>/dev/null

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

# DO NOT DELETE THIS LINE

file.o: file.h map.h
main.o: map.h file.h ncurses.h
ncurses.o: ncurses.h
map.o: map.h

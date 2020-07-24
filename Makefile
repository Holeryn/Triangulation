SRC_FILES = predicates.c triangulitation.c area.c include/gfx.c
CC_FLAGS = -g -Wall -Wextra -lX11
CC = c99

all:
	${CC} ${SRC_FILES} ${CC_FLAGS} -o triangulitation.o
clean:
	rm -rf *~ *.o

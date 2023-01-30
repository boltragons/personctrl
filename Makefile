TOOLCHAN := gcc
FLAGS := -lm -Wall -Iinc
SOURCES := src/main.c src/person.c src/personlist.c src/manager.c
EXECUTABLE := build/personctrl

all: ${SOURCES}
	@${TOOLCHAN} ${FLAGS} ${SOURCES} -o ${EXECUTABLE}

clean:
	@rm -rf ${EXECUTABLE}
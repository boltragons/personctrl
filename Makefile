TOOLCHAN := gcc
FLAGS := -lm -Wall -Iinc
MAIN_PROJECT := src/main.c 
TEST_PROJECT := src/test.c 
SOURCES := src/person.c src/personlist.c src/manager.c
EXECUTABLE := build/personctrl

all: ${SOURCES}
	@${TOOLCHAN} ${FLAGS} ${MAIN_PROJECT} ${SOURCES} -o ${EXECUTABLE}

test: ${SOURCES}
	@${TOOLCHAN} ${FLAGS} ${TEST_PROJECT} ${SOURCES} -o ${EXECUTABLE}

clean:
	@rm -rf ${EXECUTABLE}
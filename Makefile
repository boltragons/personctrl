FLAGS := -Wall -Iinc

.PHONY: clean

all: build/ bin/ bin/personctrl

test: build/ bin/ bin/tester

bin/personctrl: build/main.o build/manager.o build/personlist.o build/person.o
	${CC} ${FLAGS} $^ -o $@

bin/tester: build/test.o build/manager.o build/personlist.o build/person.o
	${CC} ${FLAGS} $^ -o $@

build/main.o: src/main.c inc/manager.h
	${CC} ${FLAGS} -c $< -o $@

build/test.o: src/test.c inc/person.h inc/personlist.h
	${CC} ${FLAGS} -c $< -o $@

build/manager.o: src/manager.c inc/manager.h inc/person.h inc/personlist.h
	${CC} ${FLAGS} -c $< -o $@

build/personlist.o: src/personlist.c inc/personlist.h inc/person.h 
	${CC} ${FLAGS} -c $< -o $@

build/%.o: src/%.c inc/%.h
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -rf bin/* build/*

%/:
	mkdir -p $@

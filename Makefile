.PHONY: all clean mac-deps run doc docker

NONTEST_C = $(shell find src -name '*.c' -not -name 'test.c')
NONMAIN_C = $(shell find src -name '*.c' -not -name 'main.c')
CFLAGS = -std=c17 -Wall -Werror -fsanitize=address -Iinclude
CC = cc
ALL_H = $(shell find . -name '*.h')

abaft: ${NONTEST_C} ${ALL_H}
	${CC} ${CFLAGS} -o abaft ${NONTEST_C}

all: clean doc abaft test

mac-deps:
	brew install clang-format

test: src/*.c ${ALL_H} Makefile
	${CC} ${CFLAGS} -o test ${NONMAIN_C}
	./test

clean:
	rm -f abaft test

run: abaft
		echo 1 2 3 | ./abaft

doc:
	python updatereadme.py

docker:
	docker build -t abaft .

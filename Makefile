.PHONY: all clean mac-deps run doc docker

PROG = abaft
NONTEST_C = $(shell find src -name '*.c' -not -name 'test.c')
NONMAIN_C = $(shell find src -name '*.c' -not -name 'main.c')
CFLAGS = -Iinclude -std=c17 -Wall -Werror -fsanitize=address
CC = cc
ALL_H = $(shell find . -name '*.h')

${PROG}: ${NONTEST_C} ${ALL_H}
	${CC} -o ${PROG} ${NONTEST_C} ${CFLAGS}

all: clean doc ${PROG} test

mac-deps:
	brew install clang-format

test: src/*.c ${ALL_H} Makefile
	${CC} -o test ${NONMAIN_C} ${CFLAGS}
	./test

clean:
	rm -f ${PROG} test

run: ${PROG}
		echo 1 2 3 | ./${PROG}

doc:
	python updatereadme.py

docker:
	docker build -t abaft .

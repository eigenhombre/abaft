.PHONY: all clean mac-deps tidy run doc docker

PROG = abaft
NONTEST_C = $(shell find . -name '*.c' -not -name 'test.c')
NONMAIN_C = $(shell find . -name '*.c' -not -name 'main.c')
CFLAGS = -std=c17 -Wall -fsanitize=address
CC = clang

${PROG}: ${NONTEST_C} *.h
	${CC} -o ${PROG} ${NONTEST_C} ${CFLAGS}

all: clean doc tidy ${PROG} test

mac-deps:
	brew install clang-format

tidy: *.c *.h
	clang-format -i *.c *.h

test: *.c *.h Makefile
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

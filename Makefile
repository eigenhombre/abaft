.PHONY: all clean mac-deps tidy run doc
PROG = abaft
NONTEST_C = $(shell find . -name '*.c' -not -name 'test.c')
NONMAIN_C = $(shell find . -name '*.c' -not -name 'main.c')
CFLAGS = -std=c17 -Wall

${PROG}: ${NONTEST_C} *.h
	cc -o ${PROG} ${NONTEST_C} ${CFLAGS}

all: tidy ${PROG} test doc

mac-deps:
	brew install clang-format

tidy: *.c *.h
	clang-format -i *.c *.h

test: *.c *.h
	cc -o test ${NONMAIN_C} ${CFLAGS}
	./test

clean:
	rm -f ${PROG}

run: ${PROG}
		echo 1 2 3 | ./${PROG}

doc:
	python updatereadme.py

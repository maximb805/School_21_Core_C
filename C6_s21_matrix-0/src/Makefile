CC = gcc
CFLAGS = -Wall -Werror -Wextra
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
SOURCES=s21_matrix.c
OBJECTS=s21_matrix.o
OS=$(shell uname -s)

all: clean test

s21_matrix.a:
	$(CC) -c $(CFLAGS) $(SOURCES)
	ar rcs s21_matrix.a $(OBJECTS)
	ranlib s21_matrix.a

style:
	cp ./../materials/linters/.clang-format .
	clang-format -n ./*.c ./*.h

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./s21_tests

test: s21_matrix.a
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) unit_tests.c s21_matrix.a -o s21_tests $(LIBS)
else
	gcc $(CFLAGS) unit_tests.c s21_matrix.a -o s21_tests $(LIBS) $(LINUX)
endif
	./s21_tests

gcov_report: clean
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage unit_tests.c $(SOURCES) -o s21_tests $(LIBS)
else
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage unit_tests.c $(SOURCES) -o s21_tests $(LIBS) $(LINUX)
endif
	./s21_tests
	lcov -t "test" -o test.info -c -d .
	lcov --remove test.info $(shell pwd)/unit_tests.c -o test.info
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf s21_tests *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report

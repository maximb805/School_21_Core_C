CC = gcc
CFLAGS = -Wall -Werror -Wextra
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
SOURCES=s21_buffer_decimal_service.c s21_decimal.c s21_compare.c s21_print_service.c s21_service.c s21_other.c s21_arithmetics.c
OBJECTS=s21_buffer_decimal_service.o s21_decimal.o s21_compare.o s21_print_service.o s21_service.o s21_other.o s21_arithmetics.o
OS=$(shell uname -s)

all: clean test

s21_decimal.a:
	$(CC) -c $(CFLAGS) $(SOURCES)
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

style:
	cp ./../materials/linters/.clang-format .
	clang-format -n ./*.c ./*.h

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./s21_tests

test: s21_decimal.a
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) unit_tests.c s21_decimal.a -o s21_tests $(LIBS)
else
	gcc $(CFLAGS) unit_tests.c s21_decimal.a -o s21_tests $(LIBS) $(LINUX)
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
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf s21_decimal s21_tests *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report

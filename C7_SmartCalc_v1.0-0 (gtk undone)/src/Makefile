CC = gcc
CFLAGS = -Wall -Werror -Wextra
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
SOURCES=s21_smart_calc.c s21_stack.c s21_parser.c s21_smart_calc.c
OBJECTS=s21_smart_calc.o s21_stack.o s21_parser.o s21_smart_calc.o
OS=$(shell uname -s)

all: clean start

s21_smart_calc.a:
	$(CC) -c $(CFLAGS) $(SOURCES)
	ar rcs s21_smart_calc.a $(OBJECTS)
	ranlib s21_smart_calc.a

style:
	cp ./../materials/linters/.clang-format .
	clang-format -n ./*.c ./*.h

valgrind: clean build
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./calc
#--show-leak-kinds=definite

test: s21_smart_calc.a
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) unit_tests.c s21_smart_calc.a -o s21_tests $(LIBS)
else
	gcc $(CFLAGS) unit_tests.c s21_smart_calc.a -o s21_tests $(LIBS) --libs gtk+-3.0 $(LINUX)
endif
	./s21_tests

build:
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) unit_tests.c s21_smart_calc.a -o s21_tests $(LIBS)
else
	gcc s21_smart_calc.c s21_parser.c s21_stack.c -o calc `pkg-config --cflags --libs gtk+-3.0` -lm
endif

start: build
	./calc

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
	rm -rf s21_tests calc *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report

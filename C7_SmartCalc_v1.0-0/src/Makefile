CC = gcc
CFLAGS = -Wall -Werror -Wextra
SOURCES=s21_smart_calc.c s21_stack.c s21_parser.c s21_credit_calc.c
OBJECTS=s21_smart_calc.o s21_stack.o s21_parser.o s21_credit_calc.o
OS=$(shell uname -s)

ifeq ($(OS), Darwin)
	LIBS = -lcheck
else
	LIBS = -lcheck -lsubunit -lrt -lm -lpthread -g
endif

all: install open

s21_smart_calc.a:
	$(CC) -c $(CFLAGS) $(SOURCES)
	ar rcs s21_smart_calc.a $(OBJECTS)
	ranlib s21_smart_calc.a

style:
	cp ./../materials/linters/.clang-format .
	clang-format -n ./*.c ./*.h ./ui/*.h ./ui/*.cpp

valgrind: clean test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./s21_tests

test: clean s21_smart_calc.a
	gcc $(CFLAGS) unit_tests.c s21_smart_calc.a -o s21_tests $(LIBS)
	./s21_tests

install:
	mkdir -p ../build && cd ../build && cmake ../src/ui && make

uninstall:
	rm -rf ../build

dist:
	mkdir -p ../SmartCalc_v1.0/
	cp -a ../build/* ../SmartCalc_v1.0
	cd ../ && tar -cvzf SmartCalc_v1.0.tar.gz SmartCalc_v1.0 && rm -rf SmartCalc_v1.0

dvi:
	open readme.html

open:
ifeq ($(OS), Darwin)
	open ../build/SmartCalc.app
else
	../build/SmartCalc
endif

gcov_report:
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage unit_tests.c $(SOURCES) -o s21_tests $(LIBS)
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
	rm -rf *.dvi

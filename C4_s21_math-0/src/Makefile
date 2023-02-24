CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
OS=$(shell uname -s)

all: clean test

s21_math.a:
	$(CC) -c $(CFLAGS) s21_math.c
	ar rcs s21_math.a s21_math.o
	ranlib s21_math.a

style:
	cp ./../materials/linters/.clang-format .
	clang-format -n ./*.c ./*.h

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./s21_test

test: s21_math.a
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) s21_test.c s21_math.a -o s21_test $(LIBS)
else
	gcc $(CFLAGS) s21_test.c s21_math.a -o s21_test $(LIBS) $(LINUX)
endif
	./s21_test

gcov_report: clean
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage s21_test.c s21_math.c -o s21_test $(LIBS)
else
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage s21_test.c s21_math.c -o s21_test $(LIBS) $(LINUX)
endif
	./s21_test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf s21_math s21_test *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBS = -lcheck
LINUX = -lsubunit -lrt -lpthread -lm
OS = $(shell uname -s)
LFLAGS = -fprofile-arcs -ftest-coverage

all: test

s21_string.a:
	$(CC) -c $(CFLAGS) s21_string.c 
	ar rcs s21_string.a s21_string.o 

s21_string_test.o:
	$(CC) -c $(CFLAGS) s21_string_test.c

test: s21_string.a s21_string_test.o
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) s21_string_test.o s21_string.a -o s21_string_test $(LIBS)
else
	$(CC) s21_string_test.o s21_string.a -o s21_string_test $(LIBS) $(LINUX)
endif
	./s21_string_test

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_string_test.c s21_string.c -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_string_test.c s21_string.c -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o ./report test.info
	open ./report/index.html

rebuild: clean
	make

style:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n ./*.c ./*.h

clean:
	rm -rf s21_string_test *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report
	rm -rf gcov_test
	rm -rf test.out

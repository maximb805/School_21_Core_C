CC = gcc
CFLAGS = -Wall -Werror -Wextra
SOURCES=./C/s21_affine_transformations.c ./C/s21_list.c ./C/s21_obj_parser.c
OBJECTS=s21_affine_transformations.o s21_list.o s21_obj_parser.o
OS=$(shell uname -s)

ifeq ($(OS), Darwin)
	LIBS = -lcheck
else
	LIBS = -lcheck -lsubunit -lrt -lm -lpthread -g
endif

all: uninstall install open

s21_3dViewer.a:
	$(CC) -c $(CFLAGS) $(SOURCES)
	ar rcs s21_3dViewer.a $(OBJECTS)
	ranlib s21_3dViewer.a

style:
	cp ./../materials/linters/.clang-format .
	clang-format -i ./C/*.c ./C/*.h ./CPP/*.h ./CPP/*.cpp ./CPP/QtGifImage/src/3rdParty/giflib/*.c ./CPP/QtGifImage/src/3rdParty/giflib/*.h \
	./CPP/QtGifImage/src/gifimage/doc/snippets/*.cpp ./CPP/QtGifImage/src/gifimage/*.cpp ./CPP/QtGifImage/src/gifimage/*.h

valgrind: clean test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./s21_tests

test: clean s21_3dViewer.a
	gcc $(CFLAGS) ./C/s21_unit_tests.c s21_3dViewer.a -o s21_tests $(LIBS)
	./s21_tests

install:
	mkdir -p ../build && cd ../build && cmake ../src/CPP && make

uninstall:
	rm -rf ../build

dist:
	mkdir -p ../3dViever_v1.0/
	cp -a ../build/* ../3dViever_v1.0
	cd ../ && tar -cvzf 3dViever_v1.0.tar.gz 3dViever_v1.0 && rm -rf 3dViever_v1.0

dvi:
	open readme.html

open:
ifeq ($(OS), Darwin)
	open ../build/3dViever.app
else
	../build/3dViewer
endif

gcov_report:
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage ./C/s21_unit_tests.c $(SOURCES) -o s21_tests $(LIBS)
	./s21_tests
	lcov -t "test" -o test.info -c -d .
	lcov --remove test.info $(shell pwd)/C/s21_unit_tests.c -o test.info
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf s21_tests *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report
	rm -rf *.dvi

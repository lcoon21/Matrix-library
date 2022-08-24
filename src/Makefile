CFLAGS = -c -Wall -Werror -Wextra -std=c++17
LDFLAGS = -O2 -Wall -Werror -Wextra -std=c++17
SOURCE = $(wildcard s21_*.cpp)
OBJECTS = $(patsubst %.cpp,%.o, ${SOURCE})

all: clean s21_matrix_oop.a test

s21_matrix_oop.a: s21_matrix_oop.cpp
	g++ $(CFLAGS) s21_matrix_oop.cpp
	ar rc $@ $(OBJECTS)
	ranlib $@
	cp $@ lib$@

test: tests.cpp s21_matrix_oop.a
	g++ $(LDFLAGS) -o test.o $^ -lgtest -lgtest_main
	./test.o

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=cpp s21_matrix_oop.cpp
	python3 ../materials/linters/cpplint.py --extension=h s21_matrix_oop.h
	# CK_FORK=no leaks --atExit -- ./test.o

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.a *.o

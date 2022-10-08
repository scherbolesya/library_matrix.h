CC=gcc
SRC=s21_matrix.c
OBJ=s21_matrix.o
CFLAGS=-Wall -Werror -Wextra -std=c11 --pedantic
TESTFLAGS=-lcheck -lm -lpthread
TFLAGS = `pkg-config --cflags --libs check` -lc -lm -ldl --coverage

ifeq ($(PLATFORM), Linux)
OPEN = xdg-open
else
OPEN = open
endif

all: s21_matrix.a test gcov_report

gcov_report: test
	lcov -t "gcov_report" -o test.info -c -d .
	genhtml -o gcov_report test.info
	$(OPEN) ./gcov_report/index.html

test: s21_matrix.a
	$(CC) *.c -o test_check $(CFLAGS) $(TFLAGS) s21_matrix.a
	./test_check

s21_matrix.a: $(OBJ) s21_matrix.h
	ar rcs s21_matrix.a $(OBJ)
	ranlib s21_matrix.a

clean:
	rm -rf *.o
	rm -rf *.gc*
	rm -rf test
	rm -rf a.out
	rm -rf ./gcov_report
	rm *.info
	rm test_check
	rm *.a

check:
	clang-format -n *.c *.h
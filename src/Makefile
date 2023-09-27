CC = gcc
FLAG_C = -c
CFLAGS = -Wall -Werror -Wextra -std=c11
SRC_C = s21_*.c
SRC_O = s21_*.o
SRC_COV = cov_*.o
GKOVFLAGS = -lgcov --coverage
TESTS_SOURSES = ./calculation.check
CHECKFLAGS = -lcheck
OS = $(shell uname)
ifeq ($(OS), Linux)
CHECKFLAGS += -lm -lpthread -lsubunit -lrt
endif

all: clean s21_calculation.a  clean

s21_calculation.a:
	$(CC) $(FLAG_C) $(CFLAGS) $(SRC_C)
	ar rc s21_calculation.a $(SRC_O)
	ranlib s21_calculation.a

test: clean s21_calculation.a
	checkmk clean_mode=1 calculation.check s21_smartcalc.h > test.c
	$(CC) test.c $(CHECKFLAGS) -lm -lcheck s21_calculation.a -o test
	./test

gcov_report:
	$(CC) -fprofile-arcs -ftest-coverage test.c s21_calc.c -o gcov_report $(CHECKFLAGS)
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

report: test gcov_report open

open:
	open -a "Google Chrome" report/src/index.html

clean:
	rm -rf test.c *.o test
	rm -rf $(SRC_O) *.a
	rm -rf *.gcov *.gcda *.gcno *.out *.info *.txt
	rm -rf gcov_report

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	rm CPPLINT.cfg
	clang-format -style=Google -n *.c *.h

leaks: test
	CK_FORK=no leaks --atExit -- ./test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test


testing.a:
	$(CC) $(FLAG_C) $(CFLAGS) $(SRC_C)
	ar rc testing.a $(SRC_O)
	ranlib testing.a

testing: clean testing.a
	$(CC) testing.c $(CHECKFLAGS)  testing.a -o testing
	./testing

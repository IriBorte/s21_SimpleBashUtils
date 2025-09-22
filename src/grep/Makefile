FLAGS=-Wall -Wextra -Werror -std=c11 -pedantic
CHECK=leaks -atExit --
FILES=tests/test_1.txt tests/test_2.txt tests/test_3.txt
PATTERNS=tests/patterns.reg

all: s21_grep

s21_grep: clean
	gcc $(FLAGS) s21_grep.c -o s21_grep

test: s21_grep
	sh tests/tests_grep.sh

style_n:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -f .clang-format

style_i:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -f .clang-format

check: s21_grep
	$(CHECK) ./s21_grep int $(FILES)
	$(CHECK) ./s21_grep -e for -e while $(FILES)
	$(CHECK) ./s21_grep -f $(PATTERNS) $(FILES)
	
rebuild: clean all

clean:
	rm -f s21_grep
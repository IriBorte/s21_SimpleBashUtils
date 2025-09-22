FLAGS =-Wall -Wextra -Werror -std=c11 -pedantic

all: s21_cat

s21_cat: clean
	gcc $(FLAGS) s21_cat.c -o s21_cat

test: rebuild
	sh tests/tests_cat.sh

style_n:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	rm -f .clang-format

style_i:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -f .clang-format
	
rebuild: clean all

clean:
	rm -f s21_cat
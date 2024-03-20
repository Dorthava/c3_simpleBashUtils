CC = gcc
C_FLAGS = -Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(C_FLAGS) s21_cat.c -o s21_cat

rebuild:
	clean
	make s21_cat

clean:
	rm -rf s21_cat
	rm -rf cat
	rm -rf s21_cat_test

leaks:
	leaks -atExit -- ./s21_cat -b text.txt
	leaks -atExit -- ./s21_cat -e text.txt
	leaks -atExit -- ./s21_cat -n text.txt
	leaks -atExit -- ./s21_cat -s text.txt
	leaks -atExit -- ./s21_cat -t text.txt
	leaks -atExit -- ./s21_cat -v text.txt
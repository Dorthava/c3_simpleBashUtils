CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: s21_grep

re: clean s21_grep

s21_grep: s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

clean:
	rm -rf s21_grep
	rm -rf s21_grep_test
	rm -rf grep
#ifndef S_21_CAT_C
#define S_21_CAT_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2048
char *fileName[SIZE];

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int file_open;
  int status;
} options;

void init_struct(options *opt);
int flag_check(char **argv, int i, int x, options *opt);
int parse_flags(int argc, char **argv, options *opt);
char v_flag(options *opt, char file_simb);
void s21_cat(int argc, char **argv, options *opt);
void s21_print(char file_simb, options *opt);

#endif  // S_21_CAT_C
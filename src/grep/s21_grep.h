#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int v;
  int c;
  int l;
  int n;
  int i;
  int s;
  int h;
  int f;
  int o;
  int error_flag;
} options;

void init_struct(options *opt);
void check_flag(int argc, char *argv[], options *opt, char *template_string,
                int size, int *count_template);
void template_e(char *optarg, int *e_flag_count, char *template_string);
void file_f(char *optarg, char *template_string, int size, int *count_template,
            options *opt);
void s21_grep(int argc, char *argv[], options *opt, char *template_string,
              int size);
void print_str(options *opt, int str_num, char *str, char *argv[],
               int count_file);

#endif  // S21_GREP_H

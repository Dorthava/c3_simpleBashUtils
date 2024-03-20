#include "s21_cat.h"
int main(int argc, char **argv) {
  options opt;
  init_struct(&opt);
  s21_cat(argc, argv, &opt);
}
void init_struct(options *opt) {
  opt->b = 0;
  opt->e = 0;
  opt->n = 0;
  opt->s = 0;
  opt->t = 0;
  opt->v = 0;
  opt->file_open = 0;
  opt->status = 1;
}
void GNU_check_flags(int x, char **argv, options *opt) {
  if (!strcmp(argv[x], "--number-nonblank")) {
    opt->b = 1;
  } else if (!strcmp(argv[x], "--number")) {
    opt->n = 1;
  } else if (!strcmp(argv[x], "--squeeze-blank")) {
    opt->s = 1;
  }
}
int flag_check(char **argv, int i, int x, options *opt) {
  switch (argv[x][i]) {
    case 'b':
      opt->b = 1;
      break;
    case 's':
      opt->s = 1;
      break;
    case 'n':
      opt->n = 1;
      break;
    case 'T':
      opt->t = 1;
      break;
    case 'v':
      opt->v = 1;
      break;
    case 't':
      opt->t = 1;
      opt->v = 1;
      break;
    case 'e':
      opt->e = 1;
      opt->v = 1;
      break;
    case 'E':
      opt->e = 1;
      break;
    default:
      fprintf(stderr, "s21_cat: invalid option -- '%c'\n", argv[x][i]);
      opt->status = 0;
      break;
  }
  return opt->status;
}
int parse_flags(int argc, char **argv, options *opt) {
  int status = 1;
  int k = 0;
  for (int x = 1; x < argc; x++) {
    if (argv[x][0] == '-' && argv[x][1] == '-' && opt->file_open != 1) {
      GNU_check_flags(x, argv, opt);
    } else if (argv[x][0] == '-' && argv[x][1] != '-' && opt->file_open != 1) {
      for (int i = 1; argv[x][i]; i++) {
        status = flag_check(argv, i, x, opt);
      }
    } else {
      opt->file_open = 1;
      fileName[k] = argv[x];
      k++;
    }
    if (opt->b == 1) opt->n = 0;
  }
  return status;
}

void s21_cat(int argc, char **argv, options *opt) {
  if (argc > 1) {
    if (parse_flags(argc, argv, opt)) {
      for (int i = 0; fileName[i]; i++) {
        FILE *fp;
        fp = fopen(fileName[i], "r");
        if (fp != NULL) {
          char file_simb = '\0';
          int ENTERs = 0;
          int num = 1;
          char previous_char = '\n';
          while ((file_simb = fgetc(fp)) != EOF) {
            if (opt->s && file_simb == '\n' && previous_char == '\n') {
              ENTERs += 1;
              if (ENTERs > 1) continue;
            } else {
              ENTERs = 0;
            }
            if (opt->b && file_simb != '\n' &&
                previous_char == '\n') {  // flag b
              printf("%6d\t", num++);
            }
            if (opt->n && previous_char == '\n') {  // flag n
              printf("%6d\t", num++);
            }
            s21_print(file_simb, opt);
            previous_char = file_simb;
          }
          fclose(fp);
        } else {
          fprintf(stderr, "s21_cat: %s: No such file or directory\n",
                  fileName[i]);
        }
      }
    }
  }
}
void s21_print(char file_simb, options *opt) {
  int prevT = 0;
  if (opt->e == 1 && file_simb == '\n') {  // flag e
    printf("%c", '$');
  }
  if (opt->t && file_simb == '\t') {  // flag t
    printf("%c%c", '^', 'I');
    prevT = 1;
  }
  file_simb = v_flag(opt, file_simb);  // flag v
  if (!prevT) {
    printf("%c", file_simb);
  }
}
char v_flag(options *opt, char file_simb) {
  int char_int = (int)file_simb;
  if (opt->v) {  // flag v
    if (char_int >= 0 && char_int <= 31 && char_int != 10 && char_int != 9) {
      printf("%c", '^');
      char_int += 64;
    } else if (char_int == 127) {
      printf("%c", '^');
      char_int = '?';
    } else if (char_int >= 128 && char_int <= 159) {
      printf("M-^");
      char_int -= 64;
    } else if (char_int > 160 && char_int <= 255) {
      char_int -= 128;
    }
  }
  file_simb = char_int;
  return file_simb;
}
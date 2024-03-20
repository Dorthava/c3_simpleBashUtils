#include "s21_grep.h"

int main(int argc, char *argv[]) {
  options opt;
  const int size = 2048;
  char template_string[size];
  template_string[0] = '\0';
  int num_in_optind = 0;
  int count_template = 0;
  init_struct(&opt);
  check_flag(argc, argv, &opt, template_string, size, &count_template);
  if (!opt.error_flag) {
    if (argc > 1) {
      if (!opt.e && !opt.f) {
        while (*(argv[optind] + num_in_optind) != '\0') {
          template_string[num_in_optind] = *(argv[optind] + num_in_optind);
          if (template_string[num_in_optind] == '\n') {
            template_string[num_in_optind] = '\0';
          }
          num_in_optind += 1;
        }
        template_string[num_in_optind] = '\0';
        count_template += 1;
        optind += 1;
      }
      s21_grep(argc, argv, &opt, template_string, size);
    } else {
      fprintf(stderr, "Usage: ./s21_grep [OPTION]... PATTERNS [FILE]...\n");
    }
  }
  return 0;
}

void init_struct(options *opt) {
  opt->c =
      0;  // Выводит ТОЛЬКО количество совпадающих строк. comp! - priority 2
  opt->e = 0;  // Шаблон
  opt->l = 0;  // Выводит ТОЛЬКО совпадающие файлы. - priority 1 - не работает с
  opt->n = 0;  // Предваряет каждую строку вывода номером строки из файла ввода.
  opt->v = 0;  // Инвертирует смысл поиска соответствий.
  opt->i = 0;  // игнорирование различий в регистре
  opt->s = 0;  // игнорируем сообщения об ошибке
  opt->h = 0;  // Выводит совпадающие строки, не предваряя их именами файлов.
  opt->f = 0;  // Получает регулярные выражения из файла.
  opt->o = 0;  // Печатает ТОЛЬКО совпадающие (непустые) части совпавшей строки.
  opt->error_flag = 0;
}

void check_flag(int argc, char *argv[], options *opt, char *template_string,
                int size, int *count_template) {
  int flag_num = 0;
  while ((flag_num = getopt(argc, argv, "e:ivclnshf:o")) != -1) {
    switch (flag_num) {
      case 'c':
        opt->c = 1;
        break;
      case 'e':
        opt->e = 1;
        template_e(optarg, count_template, template_string);
        break;
      case 'i':
        opt->i = 1;
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case 'f':
        opt->f = 1;
        file_f(optarg, template_string, size, count_template, opt);
        break;
      case 'o':
        opt->o = 1;
        break;
      default:
        opt->error_flag = 1;
        break;
    }
  }
}

void template_e(char *optarg, int *count_template, char *template_string) {
  char *ptr = template_string + strlen(template_string);
  if (*count_template != 0) {
    char ch = '|';
    *ptr++ = ch;
  }
  while (*optarg != '\0') {
    *ptr++ = *optarg++;
  }
  *count_template += 1;
  *ptr = '\0';
}

void file_f(char *optarg, char *template_string, int size, int *count_template,
            options *opt) {
  FILE *file_f = NULL;
  file_f = fopen(optarg, "r");
  if (file_f != NULL) {
    char str[size];
    char *ptr = template_string + strlen(template_string);
    while ((fgets(str, size, file_f) != NULL)) {
      char *ptr_source = str;
      if (*count_template != 0) {
        char ch = '|';
        *ptr++ = ch;
      }
      while (*ptr_source != '\0') {
        *ptr++ = *ptr_source++;
      }
      *count_template += 1;
      *ptr = '\0';
    }
    fclose(file_f);
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", optarg);
    opt->error_flag = 1;
  }
}
void s21_grep(int argc, char *argv[], options *opt, char *template_string,
              int size) {
  FILE *fp = NULL;
  int count_file = argc - optind;
  for (; optind < argc; optind++) {
    int matchOnLine = 0;
    int str_num = 0;
    fp = fopen(argv[optind], "r");
    if (fp == NULL) {
      if (!opt->s) {
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                argv[optind]);
      }
    } else {
      regex_t preg;
      int err = 0;
      char str[size];
      opt->i = (opt->i == 1) ? REG_ICASE : 0;
      if (opt->i == REG_ICASE) {
        err = regcomp(&preg, template_string, opt->i | REG_EXTENDED);
      } else {
        err = regcomp(&preg, template_string, REG_EXTENDED | 0);
      }
      if (err) {
        fprintf(stderr, "Could not compile regex\n");
        exit(0);
      }
      while (feof(fp) == 0) {
        while (fgets(str, size, fp)) {
          if (opt->n) {
            str_num++;
          }
          if (opt->l && opt->v) {
            if (regexec(&preg, str, 0, NULL, 0) != 0) {
              matchOnLine++;
            }
          } else if (opt->l && !opt->v) {
            if (regexec(&preg, str, 0, NULL, 0) == 0) {
              matchOnLine++;
            }
          } else if (opt->c && opt->v) {
            if (regexec(&preg, str, 0, NULL, 0) != 0) {
              matchOnLine++;
            }
          } else if (opt->c && !opt->v) {
            if (regexec(&preg, str, 0, NULL, 0) == 0) {
              matchOnLine++;
            }
          } else if (opt->o && opt->v) {
            if (regexec(&preg, str, 0, NULL, 0) != 0) {
              matchOnLine++;
            }
          } else if (opt->o && !opt->v) {
            if (regexec(&preg, str, 0, NULL, 0) == 0) {
              matchOnLine++;
            }
          } else {
            if (opt->v) {
              if (regexec(&preg, str, 0, NULL, 0) != 0) {
                print_str(opt, str_num, str, argv, count_file);
              }
            } else {
              if (regexec(&preg, str, 0, NULL, 0) == 0) {
                print_str(opt, str_num, str, argv, count_file);
              }
            }
          }
        }
      }
      if (opt->l == 1) {
        if (matchOnLine > 0) {
          fprintf(stdout, "%s\n", argv[optind]);
        }
      } else if (count_file > 1 && opt->c) {
        if (opt->h) {
          fprintf(stdout, "%d", matchOnLine);
        }
        if (!opt->h) {
          fprintf(stdout, "%s:%d\n", argv[optind], matchOnLine);
        }
      } else if (count_file > 1 && opt->o) {
        if (opt->h) {
          while (matchOnLine-- != 0) {
            printf("%s", template_string);
          }
        } else {
          while (matchOnLine-- != 0) {
            printf("%s:%s\n", argv[optind], template_string);
          }
        }
      }
      if (count_file == 1) {
        if (opt->o && !opt->l) {
          while (matchOnLine-- != 0) {
            printf("%s\n", template_string);
          }
        } else if (opt->c && !opt->l) {
          fprintf(stdout, "%d\n", matchOnLine);
        }
      }
      regfree(&preg);
      fclose(fp);
    }
  }
}

void print_str(options *opt, int str_num, char *str, char *argv[],
               int count_file) {
  if (opt->n) {
    if (count_file == 1 && opt->h) {
      fprintf(stdout, "%d:%s", str_num, str);
    } else if (count_file == 1 && !opt->h) {
      fprintf(stdout, "%d:%s", str_num, str);
    } else if (count_file > 1 && opt->h) {
      fprintf(stdout, "%d:%s", str_num, str);
    } else if (count_file > 1 && !opt->h) {
      fprintf(stdout, "%s:%d:%s", argv[optind], str_num, str);
    }
  } else {
    if (opt->h && count_file > 1) {
      fprintf(stdout, "%s", str);
    } else if (!opt->h && count_file > 1) {
      fprintf(stdout, "%s:%s", argv[optind], str);
    } else if (opt->h && count_file == 1) {
      fprintf(stdout, "%s", str);
    }
  }
  if (!opt->n && !opt->h && count_file == 1) {
    fprintf(stdout, "%s", str);
  }
}

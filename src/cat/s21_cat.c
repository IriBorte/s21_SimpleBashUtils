#include "s21_cat.h"

void print_file(FILE *file, int number_lines, int number_nonblank,
                int squeeze_blank, int show_ends, int show_tabs,
                int show_nonprinting) {
  char c, prev_c = '\n';
  int blank_line = 0;
  int line_number = 1;

  while ((c = fgetc(file)) != EOF) {
    if (squeeze_blank && c == '\n' && prev_c == '\n') {
      if (blank_line == 1) {
        prev_c = c;  // сохраняем предыдущее значение
        continue;
      }
      blank_line++;
    } else {
      blank_line = 0;
    }

    if ((number_nonblank && prev_c == '\n' && c != '\n') ||
        (number_lines && !number_nonblank && prev_c == '\n')) {
      printf("%6d\t", line_number++);
    } else if (number_nonblank && prev_c == '\n' && c == '\n' && show_ends) {
      printf("      \t");
    }

    if (show_ends && c == '\n') {
      printf("$");
    }
    if (show_tabs && c == '\t') {
      printf("^I");
      prev_c = c;  // сохраняем предыдущее значение
      continue;
    }
    if (show_nonprinting) {
      if (c >= 0 && c <= 31 && c != '\n' && c != '\t') {
        printf("^%c", c + 64);
      } else if (c == 127) {
        printf("^?");
      } else {
        printf("%c", c);
      }
    } else {
      printf("%c", c);
    }
    prev_c = c;  // обновляем предыдущее значение
  }
}

int main(int argc, char **argv) {
  if (argc == 1) {
    // Если нет аргументов, читаем из stdin
    print_file(stdin, 0, 0, 0, 0, 0, 0);
    return 0;
  }

  int number_lines = 0;
  int number_nonblank = 0;
  int squeeze_blank = 0;
  int show_ends = 0;
  int show_tabs = 0;
  int show_nonprinting = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == '-') {
        // Долгие опции
        if (strcmp(argv[i], "--number-nonblank") == 0) {
          number_nonblank = 1;
        } else if (strcmp(argv[i], "--number") == 0) {
          number_lines = 1;
        } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
          squeeze_blank = 1;
        } else if (strcmp(argv[i], "--show-ends") == 0) {
          show_ends = 1;
        } else if (strcmp(argv[i], "--show-tabs") == 0) {
          show_tabs = 1;
        } else if (strcmp(argv[i], "--show-nonprinting") == 0) {
          show_nonprinting = 1;
        } else {
          fprintf(stderr, "s21_cat: invalid option '%s'\n", argv[i]);
          exit(1);
        }
      } else {
        // Короткие опции
        for (size_t j = 1; j < strlen(argv[i]); j++) {
          switch (argv[i][j]) {
            case 'b':
              number_nonblank = 1;
              break;
            case 'e':
              show_ends = 1;
              show_nonprinting = 1;
              break;
            case 'E':
              show_ends = 1;
              break;
            case 'n':
              number_lines = 1;
              break;
            case 's':
              squeeze_blank = 1;
              break;
            case 't':
              show_tabs = 1;
              show_nonprinting = 1;
              break;
            case 'T':
              show_tabs = 1;
              break;
            case 'v':
              show_nonprinting = 1;
              break;
            default:
              fprintf(stderr, "Unknown option: -%c\n", argv[i][j]);
              exit(EXIT_FAILURE);
          }
        }
      }
    } else {
      // Открытие файла
      FILE *file = fopen(argv[i], "r");
      if (file) {
        print_file(file, number_lines, number_nonblank, squeeze_blank,
                   show_ends, show_tabs, show_nonprinting);
        fclose(file);
      } else {
        perror("Error opening file");
        exit(EXIT_FAILURE);
      }
    }
  }

  return 0;
}

#ifndef S21_CAT_H
#define S21_CAT_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Определение структуры options
typedef struct {
  int b;  // флаг для --number-nonblank
  int e;  // флаг для --show-ends
  int n;  // флаг для --number
  int s;  // флаг для --squeeze-blank
  int t;  // флаг для --show-tabs
  int v;  // флаг для --show-nonprinting
} options;

void print_file(FILE *file, int number_lines, int number_nonblank,
                int squeeze_blank, int show_ends, int show_tabs,
                int show_nonprinting);

#endif  // S21_CAT_H

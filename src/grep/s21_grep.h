#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char* pattern;
  int len_pattern;
  int mem_pattern;
} arguments;

arguments parsing_args(int argc, char* argv[]);
void add_pattern(arguments* arg, char* pattern);
void add_reg_from_file(arguments* arg, char* filepath);
void output(arguments arg, int argc, char** argv);
void process_file(arguments arg, char* path, regex_t* reg);
void output_line(char* line);
void print_match(regex_t* re, char* line);

#endif  // S21_GREP_H_

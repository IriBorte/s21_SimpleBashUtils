#include "s21_grep.h"

int main(int argc, char** argv) {
  arguments arg = parsing_args(argc, argv);
  output(arg, argc, argv);
  free(arg.pattern);
  return 0;
}

arguments parsing_args(int argc, char* argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        add_pattern(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
    }
  }
  if (arg.len_pattern == 0) add_pattern(&arg, argv[optind++]);
  if (argc - optind == 1) arg.h = 1;
  return arg;
}

void add_pattern(arguments* arg, char* pattern) {
  int n = strlen(pattern);
  if (arg->len_pattern == 0) {
    arg->pattern = malloc(1024 * sizeof(char));
    arg->pattern[0] = '\0';
    arg->mem_pattern = 1024;
  }
  if (arg->mem_pattern < arg->len_pattern + n) {
    arg->pattern = realloc(arg->pattern, arg->mem_pattern * 2);
    arg->mem_pattern *= 2;
  }
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(arguments* arg, char* filepath) {
  FILE* file = fopen(filepath, "r");
  if (file == NULL) {
    if (!arg->s) {
      perror(filepath);
      free(arg->pattern);
    }
    exit(1);
  }
  char* line = malloc(1024 * sizeof(char));
  size_t len;
  while (fgets(line, 1024, file) != NULL) {
    len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }
    add_pattern(arg, line);
  }
  free(line);
  fclose(file);
}

void output(arguments arg, int argc, char** argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) {
    perror("Error");
  }
  for (int i = optind; i < argc; i++) {
    process_file(arg, argv[i], &re);
  }
  regfree(&re);
}

void process_file(arguments arg, char* path, regex_t* reg) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    if (!arg.s) {
      regfree(reg);
      free(arg.pattern);
      perror(path);
    }
    exit(1);
  }
  char* line = malloc(1024 * sizeof(char));
  int line_count = 1;
  int c = 0;
  while (fgets(line, 1024, file) != NULL) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (result != 0 && arg.v)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o) {
          print_match(reg, line);
        } else {
          output_line(line);
        }
      }
      c++;
    }
    line_count++;
  }
  free(line);
  if (arg.c && !arg.l) {
    if (!arg.h) {
      printf("%s:", path);
    }
    printf("%d\n", c);
  }
  if (arg.l && c > 0) {
    printf("%s\n", path);
  }
  fclose(file);
}

void output_line(char* line) {
  for (size_t i = 0; i < strlen(line); i++) {
    putchar(line[i]);
  }
  if (line[strlen(line) - 1] != '\n') {
    putchar('\n');
  }
}

void print_match(regex_t* re, char* line) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(re, line + offset, 1, &match, 0);
    if (result != 0) {
      break;
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

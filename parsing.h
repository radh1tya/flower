#ifndef PARSING_H
#define PARSING_H

#define HEADING 1
#define PARAGRAPH 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  int type;
  char *content;
} MarkdownElement;

void parsing(FILE *file, FILE *fw);

MarkdownElement detect_md(char *line);
#endif

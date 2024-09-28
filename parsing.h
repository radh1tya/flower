#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum ElementType {
  HEADING = 1,
  PARAGRAPH = 2
};

typedef struct {
  int type;
  char *content;
} MarkdownElement;

void parsing(FILE *file, FILE *fw);

MarkdownElement detect_md(char *line);
#endif

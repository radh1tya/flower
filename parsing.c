#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsing.h"

MarkdownElement detect_md(char *line) {
  MarkdownElement element;
  if(line[0] == '#') {
    element.type = HEADING;
    element.content = strdup(line + 2);
  } else {
    element.type = PARAGRAPH;
    element.content = strdup(line);
  }
  return element;
}
void parsing(FILE *file, FILE *fw) {
  char line[256];
  while (fgets(line, sizeof(line), file)) {
    MarkdownElement element = detect_md(line);

    if ( element.type == HEADING ) {
      fprintf(fw, "<h1>%s</h1>\n", element.content);
    } else if (element.type == PARAGRAPH) {
      fprintf(fw, "<p>%s</p>\n", element.content);
    }

    free(element.content);
  }
}

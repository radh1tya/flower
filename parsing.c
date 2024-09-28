#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parsing.h"

MarkdownElement detect_md(char *line) {
  MarkdownElement element;
  if(line[0] == '#') {
    int count = 0;
    while (line[count] == '#') {
      count++;
    }
    element.type = count;
    element.content = strdup(line + count + 2);
  } else {
    element.type = PARAGRAPH;
    element.content = strdup(line);
  }
  return element;
}

void parsing(FILE *file, FILE *fw) {
      fprintf(fw, "<html>\n<head>\n<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n");
    fprintf(fw, "<body>\n");
    
  char line[256];
  while (fgets(line, sizeof(line), file)) {
     line[strcspn(line, "\n")] = 0;
    MarkdownElement element = detect_md(line);
    if ( element.type >= 1 && element.type <= 6 ) {
      fprintf(fw, "<h%d>%s</h%d>\n", element.type, element.content, element.type);
    } else if (element.type == PARAGRAPH) {
      fprintf(fw, "<p>%s</p>\n", element.content);
    }
    free(element.content);
  }
    fprintf(fw, "</body>\n</html>\n");
}

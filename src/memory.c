#include "memory.h"
#include <string.h>

String newstr(void) {
  return (String){
      .ptr = NULL,
      .length = 0,
  };
}

void pushchr(String *dst, int ch) {
  if (is_null(dst->ptr)) {
    dst->ptr = malloc(2);
    dst->ptr[0] = ch;
    dst->ptr[1] = '\0';
    dst->length++;

    return;
  }

  resize(dst->ptr, strlen(dst->ptr) + 1);

  dst->ptr[dst->length] = ch;
  dst->ptr[dst->length + 1] = '\0';
  dst->length++;
}

String fromstr(char *src) {
  size_t len = strlen(src);
  String template = newstr();

  template.ptr = malloc(len + 1);
  template.length = len;

  strcpy(template.ptr, src);

  return template;
}

void pushstr(String *dst, char *src) {
  if (dst == NULL)
    return;
  
  if (dst->ptr == NULL) {
    *dst = fromstr(src);
    return;
  }

  size_t len = strlen(src);
  size_t dstlen = strlen(dst->ptr);

  resize(dst->ptr, dstlen + len + 1);
  strcat(dst->ptr, src);

  dst->length = dstlen + len;
}

String copystr(String *src) {
  if (src == NULL) {
    fprintf(stderr, "The pointer cannot be NULL!\n");
    exit(EXIT_FAILURE);
  }

  if (src->ptr == NULL) {
    return newstr();
  }
  
  String template;

  template = newstr();
  template.ptr = strdup(src->ptr);
  template.length = src->length;

  return template;
}

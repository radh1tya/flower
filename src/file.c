#include "file.h"
#include "memory.h"
#include <stdint.h>

/*
 * @API
 * readstr, membaca string dari sebuah path.
 * Mereturn allocated string saat sukses, exit 1 saat error.
 * Programmer bertanggung jawab untuk mem-free memory
 *
 *
 * .bss section data list:
 * MAX_STRING_MEMORY_ALLOWED = 2 byte
 * is_alloc = 1 byte
 * cur_size_buff = 8 byte
 * total = 11 byte
 *
 *
 * pointer alignment data list:
 * file = 8 byte
 * heap_bufd = 8 byte
 * bufferline = 8 byte
 * total = 24 byte
 */
char *readstr(char *path) {
  const uint16_t MAX_STRING_MEMORY_ALLOWED = sizeof(char) * 2048;

  FILE *file;
  char *heap_buff, *bufferline;
  uint8_t is_fail;

  if (is_null(file = fopen(path, "r"))) {
    printerr("%s\n");
    exit(EXIT_FAILURE);
  }

  is_fail = is_null(bufferline = malloc(MAX_STRING_MEMORY_ALLOWED));

  if (is_fail) {
    printerr("%s\n");
    exit(EXIT_FAILURE);
  }

  is_fail = is_null(heap_buff = malloc(MAX_STRING_MEMORY_ALLOWED));

  if (is_fail) {
    printerr("%s\n");
    free(heap_buff);
    exit(EXIT_FAILURE);
  }

  while (!is_null(fgets(bufferline, MAX_STRING_MEMORY_ALLOWED, file))) {

    uint64_t cur_size_buff = strlen(heap_buff);

    if (cur_size_buff == MAX_STRING_MEMORY_ALLOWED - 1)
      // heap_buff = realloc(heap_buff, cur_size_buff +
      // MAX_STRING_MEMORY_ALLOWED);
      resize(heap_buff, cur_size_buff + MAX_STRING_MEMORY_ALLOWED);

    strcat(heap_buff, bufferline);
  }

  fclose(file);
  free(bufferline);

  return heap_buff;
}

// @TODO
String readstring(char *path) {
  FILE *file;
  String buffer;

  return buffer;
}

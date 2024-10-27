#ifndef FLOWER_MEMORY_H
#define FLOWER_MEMORY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exclusive memory allocator
// cocok untuk if-else statement
// contoh:
// int *p;
// if (is_null(p = malloc(sizeof(int)))) {
//   // do a thing
// }
#define is_null(NULLABLE) ((NULLABLE) == NULL ? 1 : 0)

// smart pointer allocation
// if NULLABLE is NULL, then its equal to malloc(SIZE_AFTER)
// if not NULLABLE size will be reallocate to SIZE_AFTER bytes
#define resize(NULLABLE, SIZE_AFTER)                                           \
  do {                                                                         \
    NULLABLE = realloc(NULLABLE, SIZE_AFTER);                                  \
  } while (0)

// sizeof() wrapper
#define size(TYPE, SIZE) (sizeof(TYPE) * SIZE)

// message wrapper for errno
// strerror() berfungsi mengubah nilai int dari errno
// yang berubah-ubah saat runtime, menjadi string yang
// berisi pesan error
#define ERROR strerror(errno)
#define printerr(FMT) fprintf(stderr, FMT, ERROR)

// ASCII-based string wrapper arround char * C
// Tipe ini mengabstraksi char *, untuk menyediakan API yang
// lebih memory-safe

#ifndef FLOWER_STRING
#define FLOWER_STRING
#define freestr(STRING)                                                        \
  do {                                                                         \
    free(STRING.ptr);                                                          \
    STRING.ptr = NULL;                                                         \
  } while (0);

typedef struct String {
  char *ptr;
#ifdef __STDDEF_H
  size_t length;
#else
  unsigned long length;
#endif
} String;

String newstr(void);
String fromstr(char *str);
String copystr(String *src);
void pushchr(String *dst, int ch);
void pushstr(String *dst, char *src);

#endif

#ifdef __cplusplus
}
#endif
#endif

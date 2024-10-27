// FLOWER MEMORY API
// API Untuk memanajemen runtime-memory di Flower
//
// Contributor:
//  - <destuawang@gmail.com> Awang
//
// Semua fungsi yang dibuat disini sangat bergantung pada
// glibc API, untuk penggunaan yang lebih optimal, disarankan
// menggunakan platform linux.

#include "memory.h"
#include <string.h>

// newstr, menginisialisasi tipe String dengan nilai awal.
// Setiap string di deklarasi, nilai variable haruslah nilai
// dari fungsi ini untuk menghindari runtime-error behaviour.
String newstr(void) {
  return (String){
      .ptr = NULL,
      .length = 0,
      .capacity = 0,
  };
}

// pushchr, menggabungkan String dengan 1 byte karakter.
void pushchr(String *dst, int ch) {
  if (is_null(dst->ptr)) {
    dst->ptr = malloc(2);
    dst->ptr[0] = ch;
    dst->ptr[1] = '\0';
    dst->length++;
    dst->capacity = 2;

    return;
  }

  if (dst->capacity > 1 && strlen(dst->ptr) < dst->capacity - 1) {
    dst->ptr[dst->length] = ch;
    dst->length++;
    dst->ptr[dst->length] = '\0';

    return;
  }

  resize(dst->ptr, dst->capacity++);

  dst->ptr[dst->length] = ch;
  dst->length++;
  dst->ptr[dst->length] = '\0';
}

// fromstr, Mmebuat String dari char*
// char* tidak harus memiliki heap memory.
// Fungsi ini bisa digunakan dengan char* literal
// atau const char*.
String fromstr(char *src) {
  size_t len = strlen(src);
  String template = newstr();

  template.ptr = malloc(len + 1);
  template.length = len;
  template.capacity = len + 1;

  strcpy(template.ptr, src);

  return template;
}

// pushstr, Menggabungkan char* ke String*
// Perlu diingat, String harus di pass-by refrence.
// char* tidak harus memiliki heap memory.
void pushstr(String *dst, char *src) {
  if (dst == NULL)
    return;
  
  if (dst->ptr == NULL) {
    *dst = fromstr(src);
    return;
  }

  size_t len = strlen(src);
  size_t dstlen = strlen(dst->ptr);

  if (dst->capacity > 1 && len < dst->capacity) {
    strcat(dst->ptr, src);
    dst->length += len;
    
    return;
  }

  resize(dst->ptr, dstlen + len + 1);
  strcat(dst->ptr, src);

  dst->length += len;
  dst->capacity = dst->length + 1;
}

// copystr, menyalin seluruh item String*
// termasuk:
//    ptr      = pointer ke karakter awal.
//    length   = panjang String (jumlah seluruh karakter).
//    capacity = jumlah keseluruhan heap memory (dalam bytes).
// String* HARUS di pass-by refrence.
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
  template.capacity = src->capacity;

  return template;
}

// with_capacity, menginisialisasi String dengan n-bytes heap memory.
String with_capacity(size_t size) {
  String template = newstr();

  if (is_null(template.ptr = malloc(size))) {
    printerr("%s\n");
    exit(EXIT_FAILURE);
  }

  template.capacity = size;

  return template;
}

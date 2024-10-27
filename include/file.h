#ifndef FLOWER_FILE_H
#define FLOWER_FILE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "memory.h"

char *readstr(char *path);
String read_to_string(char *path);

#ifdef __cplusplus
}
#endif
#endif

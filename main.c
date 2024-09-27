#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"

int
main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Penggunaan: %s <filename>\n", argv[0]);
    return 1;
  }
  
  FILE *fp = fopen(argv[1], "r");

  if (fp == NULL) {
    fprintf(stderr, "404\n");
    exit(1);
  }

  FILE *fw = fopen("public/output.html", "w");
  if (fw == NULL) {
    fprintf(stderr, "Galat membuat keluaran berkas\n");
    return 1;
  }

  parsing(fp,fw);
  
  fclose(fp);
  fclose(fw);
  
  return 0;
}

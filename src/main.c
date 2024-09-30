#include "../include/parsing.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#define root "post"

int is_markdown_file(const char *);

int main(void) {
  struct dirent *de;
  DIR *dr;

  dr = opendir(root);

  if (dr == NULL) {
    fprintf(stderr, "404 directory '%s' not found\n", root);
    return 1;
  }

  while ((de = readdir(dr)) != NULL) {
    if (de->d_type == DT_DIR)
      continue;

    if (is_markdown_file(de->d_name) && de->d_type == DT_REG) {

      // @WARNING Segmentation fault
      // untuk variable input file, lebih baik memorinya
      // disimpan di heap dengan malloc()
      // @TODO alokasi 256 bytes heap memori ke input_file
      char *input_file = malloc(265);
      FILE *fp;

      snprintf(input_file, 265, "post/%s", de->d_name);
      fp = fopen(input_file, "r");

      if (fp == NULL) {
        fprintf(stderr, "404 expected markdown files in %s\n", input_file);
        return 1;
      }

      char *output_file = malloc(265);
      char *ext;

      snprintf(output_file, 265, "public/%s", de->d_name);
      ext = strrchr(output_file, '.');

      if (ext != NULL) {
        strcpy(ext, ".html");
      }

      include_style();

      FILE *fw = fopen(output_file, "w");

      if (fw == NULL) {
        fprintf(stderr, "Galat membuat keluaran berkas %s\n", output_file);
        fclose(fp);

        continue;
      }

      parsing(fp, fw);
      fclose(fp);
      fclose(fw);
    }
  }

  return 0;
}

int is_markdown_file(const char *filename) {
  const char *ext = strrchr(filename, '.');

  return !strcmp(ext, ".md");
}

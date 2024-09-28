#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "parsing.h"
int is_markdown_file(const char *filename) {
  const char *ext = strrchr(filename, '.');
  return (ext && strcmp(ext, ".md") == 0);
}
int
main() {
  struct dirent *de;
  DIR *dr = opendir("post");
  if ( dr == NULL ) {
    fprintf(stderr, "404 'post'\n");
    return 1;
  }

  while ((de = readdir(dr)) != NULL) {
    if (de->d_type == DT_DIR) continue;

    if (is_markdown_file(de->d_name)) {
  char input_file[256];
  snprintf(input_file, sizeof(input_file), "post/%s", de->d_name);
      
  FILE *fp = fopen(input_file, "r");
  if (fp == NULL) {
    fprintf(stderr, "404 %s\n", input_file);
    exit(1);
  }

  char output_file[256];
  snprintf(output_file, sizeof(output_file), "public/%s", de->d_name);

  char *ext = strrchr(output_file, '.');
  if (ext != NULL) {
    strcpy(ext, ".html");
  }
  
  FILE *fw = fopen(output_file, "w");
  if (fw == NULL) {
    fprintf(stderr, "Galat membuat keluaran berkas %s\n", output_file);
    fclose(fp);
    continue;
  }
 
  parsing(fp,fw);
  
  fclose(fp);
  fclose(fw);
    }
  }
  return 0;
}

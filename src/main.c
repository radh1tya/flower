#include "../include/parsing.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

#define root "post"

int is_markdown_file(const char *);

void is_help(void) {
  fprintf(stderr, "-create to create the folders\n");
}
void create_the_folder(void) {
  mkdir("post", 0755);
  mkdir("public", 0755);
  mkdir("themes", 0755);
}
    
int main(int argc, char *argv[]) { 
  if (argc == 1) {
    fprintf(stderr, "flower - hobbyist static site generator\n");
  
    struct dirent *de;
    DIR *dr;

    dr = opendir(root);

    if (dr == NULL) {
      fprintf(stderr, "404: folder '%s' gak ketemu\n", root);
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
	
        char *input_file = malloc(256);
        if (input_file == NULL) {
          fprintf(stderr, "Gagal ngalokasiin memory ke input_file\n");
          closedir(dr);
          return 1;
        }

        snprintf(input_file, 256, "post/%s", de->d_name);
        FILE *fp = fopen(input_file, "r");

        if (fp == NULL) {
          fprintf(stderr, "404 gak ada berkasnya di %s\n", input_file);
          free(input_file);
          closedir(dr); 
          return 1;
        }
	
        char *output_file = malloc(256);
        if (output_file == NULL) {
          fprintf(stderr, "gagal ngalokasiin memory ke output_file\n");
          free(input_file);
          fclose(fp);
          closedir(dr);
          return 1;
        }

        snprintf(output_file, 256, "public/%s", de->d_name);
        char *ext = strrchr(output_file, '.');

        if (ext != NULL) {
          strcpy(ext, ".html");
        }

        include_style();

        FILE *fw = fopen(output_file, "w");

        if (fw == NULL) {
          fprintf(stderr, "Galat membuat keluaran berkas %s\n", output_file);
          fclose(fp);
          free(input_file);
          free(output_file);
          continue;
        }

        parsing(fp, fw);
        fclose(fp);
        fclose(fw);

        free(output_file);
        free(input_file);
      }
    }

    fprintf(stderr, "success!\n");
    closedir(dr);
    return 0;
  }

  else if (argc > 1 && strcmp(argv[1], "-create") == 0) {
    create_the_folder();
    return 0;
  }

  else if (argc > 1 && strcmp(argv[1], "-help") == 0) {
    is_help();
    return 0;
  }

  else {
    fprintf(stderr, "Argumen invalid: %s\n", argv[1]);
    fprintf(stderr, "Pake -help buat cari informasi\n");
    return 1;
  }
}

int is_markdown_file(const char *filename) {
  const char *ext = strrchr(filename, '.');
  return !strcmp(ext, ".md");
}

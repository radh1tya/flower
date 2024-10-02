#include "../include/parsing.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define root "post"
#if defined(DT_DIR) && defined(S_IFDIR)
#define mkdir_err(path) (mkdir(path, S_IFDIR) != 0 ? 1 : 0)
#else
#define mkdir_err(path) (mkdir(path, 0040000) != 0 ? 1 : 0)
#endif

void allocator(void *, size_t size);
void is_help(void);
int is_markdown_file(const char *);
int create_the_folder(void);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "flower\n");

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
        char *input_file = malloc(265);

        if (input_file == NULL) {
          fprintf(stderr, "Gagal ngalokasiin memory ke input_file\n");
          closedir(dr);

          return 1;
        }

        snprintf(input_file, 265, "post/%s", de->d_name);
        FILE *fp = fopen(input_file, "r");

        if (fp == NULL) {
          fprintf(stderr, "404 gak ada berkasnya di %s\n", input_file);
          free(input_file);
          closedir(dr);

          return 1;
        }

        char *output_file = malloc(265);

        if (output_file == NULL) {
          fprintf(stderr, "gagal ngalokasiin memory ke output_file\n");
          free(input_file);
          fclose(fp);
          closedir(dr);

          return 1;
        }

        snprintf(output_file, 265, "public/%s", de->d_name);
        char *ext = strrchr(output_file, '.');

        if (ext != NULL) {
          // strcpy(ext, ".html");
          // did you expect "public/foo.md.html" ?
          strcat(ext, ".html");
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

  else if (argc > 1 && strcmp(argv[1], "-version") == 0) {
    fprintf(stderr,
            "hobbyist static site generator - github.com/radh1tya/flower");

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

  if (ext == NULL) {
    perror("Berkas %s tidak ditemukan");

    // dawg, yang bawah aja udah return 1💀
    // return 1;
    return 0;
  }

  return !strcmp(ext, ".md");
}

void is_help(void) {
  // there is no need to print to stderr
  // do that to stdout instead
  fprintf(stdout, "-create to create the folders\n");
}

int create_the_folder(void) {
  int post = mkdir_err("post"), public = mkdir_err("public"),
      themes = mkdir_err("themes");

  if (post && public && themes) {
    return 1;
  }

  return 0;

  // if (mkdir("post", 0755) == -1) {
  //   perror("Gak bisa bikin folder 'post'");
  //   return 1;
  // }
  // if (mkdir("public", 0755) == -1) {
  //   perror("Gak bisa bikin folder 'public'");
  //   return 1;
  // }
  // if (mkdir("themes", 0755) == -1) {
  //   perror("Gak bisa bikin folder 'themes'");
  //   return 1;
  // }
  // return 0;
}

// @ENHANCEMENT
// function that automatically exit if
// the allocator fail
void allocator(void *dst, size_t size) {
  dst = malloc(size);

  if (dst == NULL) {
    fprintf(stderr, "Gagal alokasi %li bytes ke heap\n", size);
    exit(EXIT_FAILURE);
  }
}

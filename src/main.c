#include "file.h"
#include "option.h"
#include "memory.h"
#include <getopt.h>
#include <stdio.h>
#include <sysexits.h>

// @volatile
// agar data tidak diubah oleh sinyal OS
// seperti SIGINT, SIGHUP, SIGABRT, etc
// -Wc23-extension untuk macro @elifdef
#if defined(__linux__)
volatile int option_track;
#elif defined(_WIN32) || defined(_WIN64)
int option_track;
#endif

int main(int argc, char **argv) {

  // Program tidak menerima 1 argument, yakni $0 atau argc == 1
  // jadi jika itu terjadi, return EX_USAGE dari [sysexits.h] dan print help
  // message
  if (argc == 1) {
    char *s = readstr("src/main.c");

    printf("%s", s);
    free(s);

    return EX_USAGE;
  }

  // @CONCEPT
  // Option argument untuk flower
  // -h | --help
  // -v | --version
  struct option option[] = {
      {"help", no_argument, NULL, OPTION_HELP},
      {"version", no_argument, NULL, OPTION_VERSION},
  };

  // @FEATURES
  // option list for struct option[]
  // h = help
  // v = verison
  // bisa ditambahkan yang lain nanti
  while ((option_track = getopt_long(argc, argv, OPTION_LIST, option, NULL)) !=
         OPTION_INVALID) {

    // Semua case seperti yang terdefinisi di [option.h]
    switch (option_track) {

    case OPTION_HELP:
      printf("Help\n");

      return EX_OK;

    case OPTION_VERSION:
      printf("Version\n");

      return EX_OK;
    }
  }

  return EX_OK;
}

#include <getopt.h>
#include <stdio.h>
#include <sysexits.h>

volatile int option_track;

int main(int argc, char **argv) {

  if (argc == 1) {
    printf("Help\n");
    return EX_USAGE;
  }

  /*
   * @CONCEPT
   * Option argument untuk flower
   * -h | --help
   * -v | --version
   */
  struct option option[] = {
      {"help", no_argument, NULL, 'h'},
      {"version", no_argument, NULL, 'v'},
  };

  /*
    * @FEATURES
    * option list for struct option[]
    * h = help
    * v = verison
    * bisa ditambahkan yang lain nanti 
    */
  char *option_list = "hv";

  while ((option_track = getopt_long(argc, argv, option_list, option, NULL)) != -1) {
    switch (option_track) {
    case 'h':
      printf("Help\n");
      return EX_OK;

    case 'v':
      printf("Version\n");
      return EX_OK;
    }
  }

  return EX_OK;
}

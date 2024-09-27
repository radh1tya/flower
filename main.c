#include <stdio.h>
#include <stdlib.h>

int
main() {
  
  FILE *fp;
  char isipesan[100];
  
  fp = fopen("post/pop.md", "r");

  if (fp == NULL) {
    fprintf(stderr, "404\n");
    exit(1);
  }

  while(fgets(isipesan, 100, fp) != NULL) {
  printf("%s", isipesan);
  }
  fclose(fp);
  
  return 0;
}

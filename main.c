#include <stdio.h>
#include <stdlib.h>
void parsing(char *filecontents, FILE *fw) {

  if(filecontents[0] == '#') {
    int count = 0;

    while(filecontents[count] == '#') {
      count++;
    }
    
    fprintf(fw, "<h%d>", count);
    fprintf(fw, "%s", filecontents + count + 1);
    fprintf(fw, "</h%d>\n", count);
  }

  else {
    fprintf(fw, "<p>%s</p>\n", filecontents);
  }
  
}

int
main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Penggunaan: %s <filename>\n", argv[0]);
    return 1;
  }
  
  char *filename = argv[1];
  char filecontents[100];
  FILE *fp, *fw;

  fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "404\n");
    exit(1);
  }

  fw = fopen("output.html", "w");
  if (fw == NULL) {
    fprintf(stderr, "Galat membuat keluaran berkas\n");
    return 1;
  }

  while(fgets(filecontents, sizeof(filecontents), fp) != NULL) {
    parsing(filecontents, fw);
  }
  
  fclose(fp);
  fclose(fw);
  
  return 0;
}

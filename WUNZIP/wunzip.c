#include <stdio.h>
#include <stdlib.h>

    int count;
    char current_char;	
    
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wzip: cannot open file\n");
      exit(1);
    }
																						

    while (((int) fread(&count, sizeof (int), 1, fp)) > 0) {
      fread(&current_char, sizeof (char), 1, fp);  					

      for (int j = 0; j < count; j++) {     					
        printf("%c", current_char);
      }
    }

    fclose(fp);
  }

  return 0;
}

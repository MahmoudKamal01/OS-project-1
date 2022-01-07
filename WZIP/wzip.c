#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("wzip: file1 [file2 ...]\n");									
    exit(1);
  }

  int  count = 0;
  char previous_char;
  char current_char;

  for (int i = 1; i < argc; i++) {           		   
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wzip: cannot open file\n");
      exit(1);
    }

    while ((current_char = (char) fgetc(fp)) > 0) {     			
      if (previous_char == current_char) {                       
        count++;
      } else if (count == 0) {             		 
        count++;
        previous_char = current_char;
      } else {                                		
         fwrite(&count, sizeof (int), 1, stdout);             
         fwrite(&previous_char, sizeof (char), 1, stdout);       
         count = 1;                            		 
         previous_char = current_char;
      }
    }
    fclose(fp);
  }

        fwrite(&count, sizeof (int), 1, stdout);             
        fwrite(&previous_char, sizeof (char), 1, stdout);            // compress the last character 

  return 0;
}

/*
 * wunzip - unzip from file -> binary to text using run length encoding
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  FILE *fp;

  if (argc < 2) {
    fprintf(stdout, "wunzip: file1 [file2 ...]\n");
    exit(1);
  }

  long bsize = 0, bytes_read = 0;
  long length;
  char *filesbuf = NULL;
  // read in all files to filesbuf
  for (int i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "rb")) == NULL) {
      fprintf(stdout, "wunzip: cannot open file\n");
      exit(1);
    }
    // get length of file
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    bsize += length;
    filesbuf = realloc(filesbuf, bsize); // on first iteration equal to malloc

    // read in file
    fread(filesbuf + bytes_read, length, 1, fp);
    bytes_read += length;
  }

  long i = 0;
  long size = 8192, write_loc = 0;
  char *buf = (char *)malloc(size); // ideally should error check
  // read and write to buf
  while (i < bytes_read) {
    // get int. need some pointer trickery to translate bytes
    int *p = (int*)(&filesbuf[i]);
    int count = *p;
    char character = (char)filesbuf[i+4];
    i += 5;  // read in 5-byte chunks

    // resize buf if necessary
    if (write_loc + count > size) {
      size = size * size;
      buf = realloc(buf, size); // err check
    }

    // write to buf
    for (int j = 0; j < count; j++) {
      buf[write_loc + j] = character;
    }

    write_loc += count;
  }

  // write to stdout
  fwrite(buf, write_loc, 1, stdout);

  return 0;

}



/*
 * wzip - zip from text -> binary using run-length encoding. Output to stdout
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  FILE *fp;

  if (argc < 2) {
    fprintf(stdout, "wzip: file1 [file2 ...]\n");
    exit(1);
  }

  long bsize = 1, bytes_read = 0;
  long length;
  char *filesbuf = (char *)malloc(bsize); // malloc 1 for null term @ end
  // read in all files to filesbuf
  for (int i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "rb")) == NULL) {
      fprintf(stdout, "wgrep: cannot open file\n");
      exit(1);
    }
    // get length of file
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    bsize += length;
    filesbuf = realloc(filesbuf, bsize);

    // read in file
    fread(filesbuf + bytes_read, length, 1, fp);
    bytes_read += length;
  }
  *(filesbuf + bytes_read + 1) = '\0';  // null terminate

  int starti = 0, endi = 0;
  int counter = 0;
  unsigned long size = 8192, write_loc = 0;
  char *buf = (char *)malloc(size); // should error check
  do {
    while (filesbuf[starti] == filesbuf[endi]) {
      counter++;
      endi++;
    }
    // check size of buffer
    if (write_loc + 5 > size) {
      size = size * size;
      buf = realloc(buf, size); // should error check
    }
    // write int to buffer
    int *int_loc = (int*)(&buf[write_loc]);
    *int_loc = counter;
    write_loc += 4;
    // write char to buffer
    buf[write_loc] = filesbuf[starti];
    write_loc += 1;

    // bring lagging pointer up to leadering pointer
    starti = endi;
    counter = 0;
  } while (filesbuf[endi] != '\0');

  size_t written;
  unsigned long expected = write_loc / 5;
  if (write_loc % 5 != 0) {
    fprintf(stderr, "num bytes written not multiple of 5\n");
    exit(1);
  }
  if ((written = fwrite(buf, 5, expected, stdout)) != expected) {
    fprintf(stderr, "fwrite bad bytes: %lu vs %lu expected\n", written, write_loc);
    exit(1);
  }

  return 0;
}

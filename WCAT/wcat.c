#include <stdio.h> // for standard input and output- fgets, fclose, fopen
#include <stdlib.h> // for exit
#define BUFFER_SIZE 1000 //Buffer size=1000 characters
 
int main (int argc, char *argv[]) // argc: number of arguments including first argument as file name itself

{
for (int i=1; i<argc;i++) // Loop to sequentially process each filepath passed and display it's content
 {
 FILE *filep = fopen(argv[i], "r");// open each file in Read mode with cursor at the beginning
 if (filep == NULL) // if file path doesn't exit- exit
  {
      printf("wcat: cannot open file\n");
      exit(1); // Exit with status code = 1 
  }

 else // else read line by line and print it 
  {


  char buffer[BUFFER_SIZE]; //
  fgets(buffer,BUFFER_SIZE,filep);
// first is char * type, second is size, third should be FILE type pointer; 1 fgets outside loop ensure wcat not print previous buffer (last line) twice if passed with multiple files. 
   
  while (!feof(filep)) // print till eof is reached - "\0"
   {
   
   printf("%s", buffer);
   fgets(buffer,BUFFER_SIZE,filep);
   }
  fclose(filep); // close that file
  

  }
 }
exit(0);
}

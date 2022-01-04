#include <stdio.h>
#include <stdlib.h>    
#include <string.h>


    typedef struct{
    char c;     //Current character
    int count; //counter of the current character
}run;

int main(int argc, char *argv[])
{

FILE *fd1 = fopen("file.txt","r");
FILE *fd2 = fopen("file.z","w");

fseek(fd1,0,SEEK_END);
long size = ftell(fd1); //counts the size of fd1
rewind(fd1);
run s1;
for (int i = 0; i < size; i++)
{
    if (i == 0){   //initializes the counter and character in the 1st loop
        s1.c = fgetc(fd1);
        s1.count = 1;
    }
else{
        char cur=fgetc(fd1);
        if(s1.c == cur){
            s1.count++;
        }else{
            fprintf(fd2,"%d%c",s1.count,s1.c);
            s1.c = cur;
            s1.count = 1;
        }
    }
}

    return 0;
}

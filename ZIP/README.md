
## WZIP tool

wzip is a tool used to apply a simple form of compression to a target file. This form of compression is called run-length encoding(RLE). RLE converts n characters of the same type to number n and a single instance of the character. The file must be in exact format which is: 4-byte int and the single char.

if the target file contains the following:
aaaaabbbccd
the tool will create a text file (file.z) contains the following:
5a3b2c1d

The text file that must be provided for the pc ("file.txt") contains the first line provided above. The tool objective is to update or create a file called (file.z) which is a compressed file contains the second line.

# Testing:
In order to test the file we should open the folder terminal. Then, we write 
gcc -o wzip wzip.c -Wall -Werror
after that we write a line to the terminal:
./wzip file.txt > file.z

By doing these steps we have finished processing the code, now we go to the file and check for the desired result.

# Test Cases

*Test Case #1*
<img src="https://github.com/MahmoudKamal01/OS-project-1/blob/main/ZIP/OS%20TEST%20CASES/1.jpg" width="800" height="400" />

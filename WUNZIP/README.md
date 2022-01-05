

# WUZIP tool

WUZIP is a tool used to apply a simple form of uncompression to a target file. This form of uncompression is called run-length encoding(RLE). RLE converts  to number n and a single instance of the character to n characters of the same type. The file must be in exact format which is: 4-byte int and the single char.

if the target file contains the following:
5r3t4e
the tool will create a text file (file.txt) contains the following:
rrrrrttteeee

The file.z that must be provided for the pc ("file.z") contains the first line provided above. The tool objective is to update or create a file called (file.txt) which is a uncompressed file contains the second line.

note: put file.z in same folder with the wzip.c code source file
## Testing:
In order to test the file we should open the folder terminal. Then, we write 
`gcc -o wunzip wunzip.c -Wall -Werror`
after that we write a line to the terminal:
`./wunzip file.z > file.txt`

By doing these steps we have finished processing the code, now we go to the file and check for the desired result.

## Test Cases

*Test Case #1*
#### write : *5a7b6c4d3j* in file.z and run the program by using the two commands:
`gcc -o wunzip wunzip.c -Wall -Werror`
`./wzip file.z > file.txt`
#### file.txt will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/test1.PNG)
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/tttest1.PNG)

*Test Case #2*
#### write : *7Y5g8H7k* in file.txt and run the program by using the two commands:
`gcc -o wunzip wunzip.c -Wall -Werror`
`./wzip file.z > file.txt`
#### file.txt will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/tttest2.PNG)
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/ttest2.PNG)

*Test Case #3*
#### write : *5r3t4e* in file.txt and run the program by using the two commands:
`gcc -o wunzip wunzip.c -Wall -Werror`
`./wzip file.z > file.txt`
#### file.txt will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/test3.PNG)
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/tttest3.PNG)

*Test Case #4*
#### write : *5f7x9o7b* in file.txt and run the program by using the two commands:
`gcc -o wunzip wunzip.c -Wall -Werror`
`./wzip file.z > file.txt`
#### file.txt will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/test4.PNG)
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/testt4.PNG)

*Test Case #5*
#### write : *8i9y6t5g* in file.txt and run the program by using the two commands:
`gcc -o wunzip wunzip.c -Wall -Werror`
`./wzip file.z > file.txt`
#### file.txt will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/test6.PNG)
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WUNZIP/testt6.PNG)


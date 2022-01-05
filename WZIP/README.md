
# WZIP tool

wzip is a tool used to apply a simple form of compression to a target file. This form of compression is called run-length encoding(RLE). RLE converts n characters of the same type to number n and a single instance of the character. The file must be in exact format which is: 4-byte int and the single char.

if the target file contains the following:
aaaaabbbccd
the tool will create a text file (file.z) contains the following:
5a3b2c1d

The text file that must be provided for the pc ("file.txt") contains the first line provided above. The tool objective is to update or create a file called (file.z) which is a compressed file contains the second line.

note: put file.z in same folder with the wzip.c code source file
## Testing:
In order to test the file we should open the folder terminal. Then, we write 
`gcc -o wzip wzip.c -Wall -Werror`
after that we write a line to the terminal:
`./wzip file.txt > file.z`

By doing these steps we have finished processing the code, now we go to the file and check for the desired result.

## Test Cases

*Test Case #1*
#### write : *MMMMNS* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WZIP/OS%20TEST%20CASES/1.jpg)

*Test Case #2*
#### write : *SYSTEM* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WZIP/OS%20TEST%20CASES/2.jpg)

*Test Case #3*
#### write : *OOPPEERRAATTIINNGG* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WZIP/OS%20TEST%20CASES/3.jpg)

*Test Case #4*
#### write : *zzxxccfeaa* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WZIP/OS%20TEST%20CASES/4.jpg)

*Test Case #5*
#### write : *sssffcc* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WZIP/OS%20TEST%20CASES/5.jpg)

#### Full test Cases listed in the project description 
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WZIP/OS%20TEST%20CASES/wzipppppp.PNG)




# WCAT tool

wcat is a tool used to read a file as specified by the user and print its contents.
if the target file contains the following:
OPERATING SYSTEM
the tool will print contents of this file :
OPERATING SYSTEM
note: put file.txt in the same folder with the wcat.c code source file
## Testing:
In order to test the file we should open the folder terminal. Then, we write 
`gcc -o wcat wcat.c -Wall -Werror`
after that we write a line to the terminal:
`./wcat wcat.c`

By doing these steps we have finished processing the code, now we go to the file and check for the desired result.

## Test Cases

*Test Case #1*
#### write : *MMMMNS* in file.txt and run the program by using the two commands:
`gcc -o wcat wcat.c -Wall -Werror`
`./wcat wcat.c`
#### contents of file will be printed in the terminal
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WCAT/test%20case%201.jpg)

*Test Case #2*
#### write : *OPERATING SYSTEM* in file.txt and run the program by using the two commands:
`gcc -o wcat wcat.c -Wall -Werror`
`./wcat wcat.c`
#### contetnts of file will be printed in the terminal, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WCAT/test%20case%202.jpg)

*Test Case #3*
#### write : *TEAM PROJECT* in file.txt and run the program by using the two commands:
`gcc -o wcat wcat.c -Wall -Werror`
`./wcat wcat.c`
#### contetnts of file will be printed in the termina, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WCAT/test%20case%203.jpg)




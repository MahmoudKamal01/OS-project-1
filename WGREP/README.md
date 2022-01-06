

# grep command in Linux

The grep filter searches a file for a particular pattern of characters, and displays all lines that contain that pattern. The pattern that is searched in the file is referred to as the regular expression (grep stands for global search for regular expression and print out). 

# Syntax:

grep [options] pattern [files]

# Options available are:

-h: it prints the matched lines, but do not print the filenames.

-w : Match whole word

-o : Print only the matched parts of a matching line,
 with each such part on a separate output line.
 
-l : it prints a list of a filenames only.

-n :it prints the matched lines and their line numbers.

-c :it prints only a count of the lines that match a pattern

note: put file.z in same folder with the wzip.c code source file
## Testing:
In order to test the file we should open the folder terminal. Then, we write 
`gcc -o wgrep wgrep.c -Wall -Werror`
after that we write a line to the terminal:
`./wgrep file.txt > file.z`

By doing these steps we have finished processing the code, now we go to the file and check for the desired result.

## Test Cases

*Test Case #1*
#### write : *MMMMNS* in file.txt and run the program by using the two commands:
`gcc -o wgrep wgrep.c -Wall -Werror`
`./wgrep file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/ZIP/OS%20TEST%20CASES/1.jpg)

*Test Case #2*
#### write : *SYSTEM* in file.txt and run the program by using the two commands:
`gcc -o wgrep wgrep.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/ZIP/OS%20TEST%20CASES/2.jpg)

*Test Case #3*
#### write : *OOPPEERRAATTIINNGG* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/ZIP/OS%20TEST%20CASES/3.jpg)

*Test Case #4*
#### write : *zzxxccfeaa* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/ZIP/OS%20TEST%20CASES/4.jpg)

*Test Case #5*
#### write : *sssffcc* in file.txt and run the program by using the two commands:
`gcc -o wzip wzip.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/ZIP/OS%20TEST%20CASES/5.jpg)


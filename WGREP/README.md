

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

`gcc -o wgrep wgrep.c -Wall -Werror`
`./wgrep file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WGREP/WhatsApp%20Image%202022-01-05%20at%2011.30.00%20PM.jpeg)

*Test Case #2*

`gcc -o wgrep wgrep.c -Wall -Werror`
`./wzip file.txt > file.z`
#### file.z will be created, open it to check the result
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/WGREP/WhatsApp%20Image%202022-01-05%20at%2011.29.59%20PM.jpeg)




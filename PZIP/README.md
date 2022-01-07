
# PZIP tool

PZIP is used to zip multiple files (alpha-numeric text) parallely. This is multi-threading function that works as wzip but for multiple files at the same time.
we used an approach based on producer & consumer. We used this approach because files of different sizes usually takes control of the compression time. As the files can be of unequal sizes, work was not equally divided between threads, and so the process did not put equal load on all cores. So this approach divides 
the load equally because a producer is only required to create memory mapping for files whereas the consumers are required to compress the files.The file is broken into pages by the producer and these pages are zipped by the consumers. 


## Testing:
In order to test the file we should open the folder terminal. Then, we run the file using these two commands:

`gcc -o pzip pzip.c -Wall -Werror -pthread -O`

`./test-pzip.sh`

By doing these steps we have finished processing the code, now we go to the files and check for the desired result.

## Test Cases

#### Full test Cases listed in the project description 
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/PZIP/parallelzip.PNG)



#### Comparison between performances of wzip and pzip
![](https://github.com/MahmoudKamal01/OS-project-1/blob/main/PZIP/parallelzip.PNG)

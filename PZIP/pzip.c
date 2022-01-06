///////////////////Libraries///////////////////////
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <assert.h>

/*
global variables
*/


int total_threads; //n.o. threads created
int page_size;
int num_files; //n.o. files passed as arguments
int isComplete=0; //flag signals any sleeping thread that program ended
int total_pages;
int q_head=0;
int q_tail=0;
#define q_capacity 10

int q_size=0;

pthread_mutex_t lock;
pthread_cond_t empty , fill;
int* pages_per_file;


//struct of the compressed output
struct output {
	char* data;   // the characters
	int* count;   //characters count
	int size;
}*out;

//buffer struct contains a specific data (page) from a file
struct buffer {
    char* address; //Mapping address of the specific page number of the file number
    int file_number; //File Number
    int page_number; //Page number
    int last_page_size; //Page size
}buf[q_capacity];


//struct that compresses the buffer.
struct output RLECompress(struct buffer temp){
	struct output compressed;
	compressed.count=malloc(temp.last_page_size*sizeof(int)); //the size is determined by the worst case scenario in case there is no repeated chars
	char* tempString=malloc(temp.last_page_size);
	int countIndex=0;
	for(int i=0;i<temp.last_page_size;i++){
		tempString[countIndex]=temp.address[i];
		compressed.count[countIndex]=1;
		while(i+1<temp.last_page_size && temp.address[i]==temp.address[i+1]){
			compressed.count[countIndex]++;
			i++;
		}
		countIndex++;
	}
	compressed.size=countIndex;
	compressed.count=realloc(compressed.count, countIndex*sizeof(int)); //resize a block of memory to the proper size
	compressed.data=realloc(tempString,countIndex); // resize a block of memory that was previously allocated to it's proper size
	return compressed;
}

//Remove from q_tail index of the circular queue.
struct buffer get(){
  	struct buffer b = buf[q_tail]; //Dequeue the buffer.
	q_tail = (q_tail + 1) % q_capacity;
  	q_size--;
  	return b;
}

//functions definitions /////////////
void Pthread_mutex_lock(pthread_mutex_t *mutex);
void Pthread_cond_init(pthread_cond_t *cond,void* attr);
void Pthread_mutex_unlock(pthread_mutex_t *mutex);
void Pthread_create(pthread_t *thread, const pthread_attr_t * attr, void * (*start_routine)(void*), void * arg);
void Pthread_join(pthread_t thread, void **value_ptr);
void Pthread_mutex_init(pthread_mutex_t *mutex,void* attr);
void Pthread_mutex_init(pthread_mutex_t *mutex,void* attr);
void put(struct buffer b);
void* producer(void *arg);
int calculateOutputPosition(struct buffer temp);
void *consumer();
void printOutput();
void freeMemory();
///////////



int main(int argc, char* argv[]){
	//Check if arguments is less than two
	if(argc<2){
		printf("pzip: file1 [file2 ...]\n");
		exit(1);
	}

	page_size = 10000000;
	num_files=argc-1; //n.o. files
	total_threads=get_nprocs(); //n.o. processes consumer threads
	pages_per_file=malloc(sizeof(int)*num_files); //how many Pages per file.

    out=malloc(sizeof(struct output)* 512000*2);
	//dynamically initialize the mutex lock
	Pthread_mutex_init(&lock,NULL);

	//dynamically initialize the conditional variables
	Pthread_cond_init(&empty,NULL);

	Pthread_cond_init(&fill,NULL);

	//mapping all files through the producer thread
	pthread_t pid,cid[total_threads];
	Pthread_create(&pid, NULL, producer, argv+1); //argv + 1 to skip argv[0].

	//compressing all pages throught consumer thread
	for (int i = 0; i < total_threads; i++) {
        Pthread_create(&cid[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < total_threads; i++) {
        Pthread_join(cid[i], NULL);
    }
    Pthread_join(pid,NULL);
	printOutput();
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&fill);
	freeMemory();
	return 0;
}



////////////functions impelementations

/*
wrapper function
*/
// this function is used to make sure that our function calls are working properly
void Pthread_mutex_lock(pthread_mutex_t *mutex){
int rc = pthread_mutex_lock(mutex);
assert(rc ==0);
}

void Pthread_mutex_unlock(pthread_mutex_t *mutex){
int rc = pthread_mutex_unlock(mutex);
assert(rc ==0);
}

void Pthread_create(pthread_t *thread, const pthread_attr_t * attr, void * (*start_routine)(void*), void * arg){
int rc = pthread_create(thread,attr,start_routine,arg);
assert(rc ==0);
}

void Pthread_join(pthread_t thread, void **value_ptr){
int rc=pthread_join(thread,value_ptr);
assert(rc==0);
}

void Pthread_mutex_init(pthread_mutex_t *mutex,void* attr){
int rc=pthread_mutex_init(mutex,attr);
	assert(rc==0);
	}

void Pthread_cond_init(pthread_cond_t *cond,void* attr){
int rc=pthread_cond_init(cond,attr);
	assert(rc==0);
	}


/*
queue function
*/


//Add at q_head index of the circular queue.
void put(struct buffer b){
  	buf[q_head] = b; //Enqueue the buffer
  	q_head = (q_head + 1) % q_capacity;
  	q_size++;
}



/*
producer function
- Producer function used to memory map the files passed as arguments.
*/
void* producer(void *arg){
	//Get the file.
	char** filenames = (char **)arg;
	struct stat sb;    // this struct returns information about the file
	char* map; // contains mmap address
	int file;

	// Open the file
	for(int i=0;i<num_files;i++){

		file = open(filenames[i], O_RDONLY); // this function creates an open file description that refers to a file
		int pages_in_file=0; //this variable stores n.o. pages in a file. [n.o. pages = Size of file / Page size]
		int last_page_size=0; //Variable required if the file is not page-alligned which means (Size of File % Page size !=0)

		if(file == -1){ // condition to check if file is not found
			printf("Error: File didn't open\n");
			exit(1);
		}

		// Get the file information
		if(fstat(file,&sb) == -1){
			close(file);
			printf("Error: Couldn't retrieve file stats");
			exit(1);
		}
		//condition to check for empty files
        	if(sb.st_size==0){
               		continue;
        	}
		//Calculate n.o. pages and last page size. st_size contains the size offset.

		pages_in_file=(sb.st_size/page_size);
		//if file is not page alligned, we'll need to add a page.
		if(((double)sb.st_size/page_size)>pages_in_file){
			pages_in_file+=1;
			last_page_size=sb.st_size%page_size;
		}
		else{ //Page alligned
			last_page_size=page_size;
		}
		total_pages+=pages_in_file;
		pages_per_file[i]=pages_in_file;

		// Map the entire file.
		map = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, file, 0); //If addr is NULL, then the kernel chooses the (page-aligned) address



		if (map == MAP_FAILED) {
			close(file);
			printf("Error mmapping the file\n");
			exit(1);
    	}

		for(int j=0;j<pages_in_file;j++){
			Pthread_mutex_lock(&lock);
			while(q_size==q_capacity){
			    pthread_cond_broadcast(&fill);
				pthread_cond_wait(&empty,&lock); //signal the consumer to start working on the queue.
			}
			Pthread_mutex_unlock(&lock);
			struct buffer temp;
			if(j==pages_in_file-1){
				temp.last_page_size=last_page_size;
			}
			else{
				temp.last_page_size=page_size;
			}
			temp.address=map;
			temp.page_number=j;
			temp.file_number=i;

			map+=page_size; //jump to next page
			//there might be race condition
			Pthread_mutex_lock(&lock);
			put(temp);
			Pthread_mutex_unlock(&lock);
			pthread_cond_signal(&fill);
		}

		close(file);
	}
	//Possible race condition at isComplete?
	isComplete=1; //When producer is done mapping.
	pthread_cond_broadcast(&fill); //signal all the sleeping consumer threads to start processing
	return 0;
}


/*
consumer
*/

//Calculates buffer output position
int calculateOutputPosition(struct buffer temp){
	int position=0;

	for(int i=0;i<temp.file_number;i++){
		position+=pages_per_file[i];
	}
	//Now we're at the beginning of the file, we need to find the page relative position
	position+=temp.page_number;
	return position;
}



void *consumer(){
	do{
		Pthread_mutex_lock(&lock);
		while(q_size==0 && isComplete==0){
		    pthread_cond_signal(&empty);
			pthread_cond_wait(&fill,&lock);
		}
		if(isComplete==1 && q_size==0){ //if mapping is finished
			Pthread_mutex_unlock(&lock);
			return NULL;
		}
		struct buffer temp=get();
		if(isComplete==0){
		    pthread_cond_signal(&empty);
		}
		Pthread_mutex_unlock(&lock);
		//calculating output position
		int position=calculateOutputPosition(temp);
		out[position]=RLECompress(temp);
	}while(!(isComplete==1 && q_size==0));
	return NULL;
}




void printOutput(){
	char* finalOutput=malloc(total_pages*page_size*(sizeof(int)+sizeof(char)));
    char* init=finalOutput;
	for(int i=0;i<total_pages;i++){
		if(i<total_pages-1){
			if(out[i].data[out[i].size-1]==out[i+1].data[0]){ //check for equality between i and i+1 's first char
				out[i+1].count[0]+=out[i].count[out[i].size-1]; // merge them if they are equal
				out[i].size--;
			}
		}

		for(int j=0;j<out[i].size;j++){
			int num=out[i].count[j];
			char character=out[i].data[j];
			*((int*)finalOutput)=num;
			finalOutput+=sizeof(int); // in order to point to the next char, we increase the pointer by size of int
			*((char*)finalOutput)=character; 
            finalOutput+=sizeof(char);

		}
	}
	fwrite(init,finalOutput-init,1,stdout);
}

void freeMemory(){

	free(pages_per_file);
	for(int i=0;i<total_pages;i++){
		free(out[i].data);
		free(out[i].count);
	}
	free(out);


}

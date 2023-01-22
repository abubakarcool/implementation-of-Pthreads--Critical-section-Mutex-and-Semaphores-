
///Builds:	g++ ~/Codes/Src/Threads/ProducerConsumer.cpp -lpthread -o ~/Codes/Output/ProducerConsumer
///Runs:	~/Codes/Output/ProducerConsumer

/********************************************************************
 * Authors: Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 * This program gives a solution to the Producer Consumer Problem. It 
 * creates two threads, one producer and one consumer. The 
 * Producer threader randomly generates numbers and places them to a 
 * shared buffer (rack). The Consumer thread reads data from buffer and
 * prints the received values
 * 
 * The Program needs to take care of three things
 * 
 * 1) Producer doesn't write if the buffer (rack) is full
 * 2) Consumer doesn't read an item if the buffer (rack) is empty
 * 3) Producer and Consumer do not simultaneously access same parts
 *    of buffer (can create race condition) 
 * 
 * Important Functions:
 * 	pthread_create	creates a new posix thread, which executes 
 *			the mat_calc function provided as argument # 3
 *	pthread_join	Stops execution of main thread, until 
 *			the joined thread (specified by argument # 1) 
 *			has finished its execution   
 * 
 * 	sem_init	Initializes semaphore object to a specified value
 *  
 *  sem_destroy	frees any memory used by the semaphore object
 * 
 *  sem_wait	Decrements the value of semaphore object. If value is 
 * 				already 0, block the calling thread. The thread is kept
 * 				blocked until sem_post is called on the same semaphore
 *  sem_post	Increments the value of semaphore object. Also, 
 * 				activates one blocked thread on the same semaphore
 ********************************************************************/

#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define RACK_SIZE 10	//Shared buffer size
long rack[RACK_SIZE];	//Shared buffer between producer and consumer

sem_t mutex;//For mutual exclusion:						   = 1
sem_t full;	//Protect consumer from reading empty buffer   = 0
sem_t empty;//Protect producer from writing to full buffer = buffer size

void *Producer(void *rank);
void *Consumer(void *rank);

using namespace std;
int main() {
	pthread_t thread_handles[2];	//For Producer and Consumer Threads

	sem_init(&full, 0, 0);			//Set value to 0
	sem_init(&empty, 0, RACK_SIZE); //Set value to RACK_SIZE
	sem_init(&mutex, 0, 1);			//Set value to 1
	
	cout<<"Main thread creating Producer and Consumer Threads"<<endl;
	pthread_create(&thread_handles[0], NULL, Producer, (void *)0);
	pthread_create(&thread_handles[0], NULL, Consumer, (void *)0);
	
	//Main thread Joining the Producer and Consumer threads
	for (long thread=0; thread<2; thread++)	
		pthread_join(thread_handles[thread], NULL);

	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
	return 0;
}

//Thread function, Check the return type and parameter list
void *Producer(void *rank) {
	long number;		//To carry produced item
	int  p_index = 0;	//Where producer places data in rack;

	while (1) {
		number = rand() % 10;	//generate a random number (0-9)

		sem_wait(&empty);	//producer only writes if a slot is empty
		sem_wait(&mutex);	//mutual exclusion between producer/consumer
			cout<<"===>>"<<number<<endl;
			rack[p_index] = number;
			p_index = (p_index+1) % RACK_SIZE;
		sem_post(&mutex);
		sem_post(&full);	//inform consumer about new data 

		sleep(rand()%4 + 2);	
	} 
	return NULL; 
}

//Thread function, Check the return type and parameter list
void *Consumer(void *rank) {

	long item;			//To read item from buffer (rack) 
	int  c_index = 0;	//From where consumer collects data
	
	while(1) {
		sem_wait(&full);	//Consumer only reads if rack is not empty
		sem_wait(&mutex);	//For mutual excusion
			item = rack[c_index];
			c_index = (c_index+1) % RACK_SIZE;
			cout<<"<<====="<<item<<endl;
		sem_post(&mutex);
		sem_post(&empty);	//inform producer about new empty slot
		
		sleep(rand()%4 + 2);
	}
	return NULL;
} 

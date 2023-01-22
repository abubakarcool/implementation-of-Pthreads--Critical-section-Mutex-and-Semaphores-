///Builds:	g++ ~/Codes/Src/Threads/HelloPrint.cpp -lpthread -o ~/Codes/Output/HelloThread
///Runs:	~/Codes/Output/HelloThread

/********************************************************************
 * Authors Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 * This program creates THREAD_COUNT number of threads, with
 * each thread simultaneously running the HelloPrint function, 
 * which prints a hello message.
 *
 * Important Functions:
 * 	pthread_create	creates a new posix thread, which executes 
 *			the function provided as parameter # 3
 *	pthread_join	Stops execution of main thread, until 
 *			the joined thread (specified by parameter 1) 
 *			has finished its execution       
 ********************************************************************/

#include<iostream>
#include<pthread.h>	//Pthreads header include file

#define THREAD_COUNT 4	//Controls the number of threads

void* HelloPrint(void *rank);

using namespace std;

int main(int argc,char *argv[]) {
	pthread_t thread_handles[THREAD_COUNT];
	int a;	
	a=argv;
	THREAD_COUNT=int(a);

	//Create THREAD_COUNT number of Pthreads
	for (long thread=0; thread<THREAD_COUNT; thread++) {
		pthread_create(&thread_handles[thread], 
				NULL, HelloPrint, (void*)thread);
	}
	
	cout<<"Hello from the main thread\n";

	//Join all created Pthreads
	for (long thread=0; thread<THREAD_COUNT; thread++) {
		pthread_join(thread_handles[thread], NULL);
	}
	//This line executes after completion of joined threads
	cout<<"Main Thread Exiting\n";

	return 0;
}

//Thread function, Check the return type and parameter list
void* HelloPrint(void *rank) {
	long my_rank = (long) rank;
	cout<<"hello from thread "<<my_rank<<" of "<<THREAD_COUNT<<endl;
	return NULL;
}


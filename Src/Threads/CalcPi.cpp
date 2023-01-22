///Builds:	g++ ~/Codes/Src/Threads/CalcPi.cpp -lpthread -o ~/Codes/Output/Pi
///Runs:	~/Codes/Output/Pi

/********************************************************************
 * Authors: Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 * This program creates multiple threads to parallelize estimation 
 * for Pi. The formula used for Pi estimation is
 *  
 * Pi = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 .....) 
 * 
 * NOTE: This code carries possible race condition, as all threads 
 *       simultaneously store the results in same variable (sum)
 * 		 This means, every run of this program may produce different
 * 		 results 
 * 
 * Important Functions:
 * 	pthread_create	creates a new posix thread, which executes 
 *			the mat_calc function provided as argument # 3
 *	pthread_join	Stops execution of main thread, until 
 *			the joined thread (specified by argument # 1) 
 *			has finished its execution       
 ********************************************************************/

#include<iostream>
#include<math.h>
#include<pthread.h>

long   n;				//n decides number of runs (precision) 
double sum;				//holds the sum
long   thread_count;	//Controls the number of threads

void *Thread_Sum(void*);

using namespace std;
int main() {
	pthread_t *thread_handles;

	sum = 0.0;
	thread_count = 2;
	n = powl(10, 8);

	thread_handles = new pthread_t[thread_count]; 

	cout<<"Main thread creating "\
		<<thread_count<<" Threads for N = "<<n<<endl;

	//Create THREAD_COUNT number of Pthreads
	for (long thread=0; thread<thread_count; thread++)
		pthread_create(&thread_handles[thread], 
			NULL, Thread_Sum, (void *)thread);
			
	//Main thread joining all created threads
	for (long thread=0; thread<thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	cout.precision(8);//Printing the precise Results
	cout<<"Calculated Value for Pi is "<<4.0*sum<<endl;
	return 0;
}

//Thread function, Check the return type and parameter list
void *Thread_Sum(void *rank) {

	//identify start and end values for sum calculation 
	long i;
	double factor;
	long my_rank = (long)rank;
	long my_n = n/thread_count;
	long my_first_i = my_n*my_rank;
	long my_last_i  = my_first_i + my_n;

	if (my_rank % 2 == 0)	factor = 1.0;	//+ve or -ve sign
	else					factor = -1.0;

	//Estimate Sum
	for (i=my_first_i; i<my_last_i; i++, factor = -factor) {
		/*
		 * Possible Race condition. Sum can be simultaneously
		 * modified by multiple threads. This should be avoided
		 */ 
		sum += factor/(2.0*i+1); // <== RACE Condition,,,
	}
	return NULL; 
} 

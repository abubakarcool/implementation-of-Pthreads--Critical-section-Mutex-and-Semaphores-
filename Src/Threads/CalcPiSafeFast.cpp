///Builds:	g++ ~/Codes/Src/Threads/CalcPiSafeFast.cpp -lpthread -o ~/Codes/Output/PiSafeFast
///Runs:	~/Codes/Output/PiSafeFast

/********************************************************************
 * Authors: Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 * This program creates multiple threads to parallelize estimation 
 * for Pi. The formula used for Pi estimation is
 *  
 * Pi = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 .....) 
 * 
 * NOTE: This code resolves the race condition problem by using mutex
 * 		 Thus, the results attained are thread safe.
 * 		 However, it results in sequential execution of some code
 * 		 segments, which is not an efficient solution.
 * 
 * Important Functions:
 * 	pthread_create	creates a new posix thread, which executes 
 *			the mat_calc function provided as argument # 3
 *	pthread_join	Stops execution of main thread, until 
 *			the joined thread (specified by argument # 1) 
 *			has finished its execution   
 * 	pthread_mutex_init	Initializes mutex (pthread_mutex_t) for use
 *  
 *  pthread_mutex_destroy	frees any memory used by the mutex
 * 
 *  pthread_mutex_lock	Allows only one thread (per mutex) to pass 
 * 						through this line. Other caller threads wait
 * 						until mutex is freed by pthread_mutex_unlock
 *  pthread_mutex_unlock	Unlocks the critical section acquired by 
 * 							mutex variable, Which allows next caller
 * 							enter the critical section  
 ********************************************************************/

#include<iostream>
#include<math.h>
#include<pthread.h>

long   n;				//n decides number of runs (precision) 
double sum;				//holds the sum
long   thread_count;	//Controls the number of threads
pthread_mutex_t m_sum;	//To control mutual exclusion

void *Thread_Sum(void*);

using namespace std;
int main() {
	pthread_t *thread_handles;

	sum = 0.0;
	thread_count = 2;
	n = powl(10, 8);
	pthread_mutex_init(&m_sum, NULL);	//INITIALIZE MUTEX
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

	pthread_mutex_destroy(&m_sum);	//FREE THE MUTEX 
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
	
	double t_sum = 0.0;//Local to each thread,Holds sum for each thread

	if (my_rank % 2 == 0)	factor = 1.0;	//+ve or -ve sign
	else					factor = -1.0;

	//Estimate Sum
	for (i=my_first_i; i<my_last_i; i++, factor = -factor) {
		t_sum += factor/(2.0*i+1);//<== No Race Condition,t_sum is local
	}
  pthread_mutex_lock(&m_sum);	 
	sum += t_sum;		//Short Lived Sequential Part
  pthread_mutex_unlock(&m_sum);
	return NULL; 
} 

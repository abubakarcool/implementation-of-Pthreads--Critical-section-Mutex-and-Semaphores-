///Builds:	g++ ~/Codes/Src/Threads/MatrixMul.cpp -lpthread -o ~/Codes/Output/MatrixMul
///Runs:	~/Codes/Output/MatrixMul

/********************************************************************
 * Authors: Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 * This program multiplies an m*n matrix A with an n*1 matrix X to 
 * compute an M*1 matrix Y. The program creates thread_count number
 * of threads to parallelize the matrix vector calculation
 * 
 *
 * Important Functions:
 * 	pthread_create	creates a new posix thread, which executes 
 *			the mat_calc function provided as argument # 3
 *	pthread_join	Stops execution of main thread, until 
 *			the joined thread (specified by argument # 1) 
 *			has finished its execution       
 ********************************************************************/

#include<iostream>
#include<stdlib.h>
#include<pthread.h>		//Pthreads header include file

#define M 6
#define N 3
#define THREAD_COUNT 2	//Controls the number of threads

void* mat_calc(void *rank);

int A[M][N];	//M*N Matrix A
int X[N];		//N*1 Matrix X
int Y[M];		//M*1 Matrix Y

using namespace std;

int main() {

	pthread_t thread_handles[THREAD_COUNT]; 
	int status;		//To check for Successful Thread Creation
			
	srand(time(NULL));	//Initialize random number generator (seed)
	 
	for (int i=0; i<M; i++)	//Fill Matrix A with random values (0-10)
		for (int j=0; j<N; j++)	A[i][j] = rand()%10; 

	for (int i=0; i<N; i++)	//Fill Matrix X with random values (0-10)
		X[i] = rand()%10;

	cout<<"Main Thread Creating "<<THREAD_COUNT<<" threads"<<endl;
	//Create THREAD_COUNT number of Pthreads
	for (long thread=0; thread<THREAD_COUNT; thread++) {
		status = pthread_create(&thread_handles[thread], 
					NULL, mat_calc, (void*)thread);

		if (status != 0) {	//Successful thread creation returns 0
			cout<<"\nThread Creation Failed, Exiting!!!\n";
			exit(-1);
		}
	}
	
	//Main thread joining all created threads
	for (long thread=0; thread<THREAD_COUNT; thread++)
		pthread_join(thread_handles[thread], NULL);

	cout<<"The Results Are"<<endl;
	cout<<"\nMatrix A "<<endl;
	for (int i=0; i<M; i++) {	//Printing the product vector
		for (int j=0; j<N; j++)	cout<<A[i][j]<<"\t";
		cout<<endl;
	}

	cout<<"\nMatxix X "<<endl;
	for (int i=0; i<N; i++)
		cout<<X[i]<<endl;

	cout<<"\nMatrix Y "<<endl;
	for (int i=0; i<M; i++)
		cout<<Y[i]<<endl;

	return 0;
}

//Thread function, Check the return type and parameter list
void* mat_calc(void *rank) {
	//Calculate first and last row for matrix vector multiplication
	long my_rank = (long) rank;
	int i, j;
	int local_m = M/THREAD_COUNT;
	int my_first_row = my_rank*local_m;
	int my_last_row  = (my_rank+1)*local_m - 1;

	//Compute the corresponding rows for Y
	for (i = my_first_row; i <= my_last_row; i++) {
		Y[i] = 0.0;
		for (j=0; j<N; j++)
			Y[i] += A[i][j]*X[j];
	}
}


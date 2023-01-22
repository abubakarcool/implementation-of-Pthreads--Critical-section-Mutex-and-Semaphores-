///Builds:	g++ ~/Codes/Src/Processes/ForkSimple.cpp -o ~/Codes/Output/ForkSimple
///Runs:	~/Codes/Output/ForkSimple

/***********************************************************************
 * Authors: Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 * This program is a simple fork system call illustration. Fork creates
 * a new child process, which is an exact copy of the caller parent 
 * process. This is benificial, because parent and child might need
 * to share some information before starting separate taske
 * 
 * Important Functions:
 * fork:	Creates a child process. Two processes (parent and child) 
 * 			start executing after this line
 * wait:	Stops execution of parent process, until child has 
 * 			returned. Parent can also get child's return status (success
 * 			failure etc) and id to decide its further execution 
 ***********************************************************************/

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

	int number = 6;	//to show different copies of data with each process

	pid_t pid;		//Process ID (unsigned int, defined in sys/types.h)
	pid = fork();	//Creates new process, TWO processes run after this


	if (pid < 0) 	//Indicates fork failure
		cout<<"\nProcess Creation Failed\n";

	if (pid > 0) {	//Parent gets child's ID in PID
		cout<<"Parent Process: ID "<<getpid()<<" Child ID "<<pid<<endl;
		cout<<"Parent copy of number = "<<number<<endl;
		
		number = 4;	//Parent and child get separate copies of data!
		cout<<"Parent's New Value of Number is : "<<number<<endl;
		cout<<"Parent Process Going to Wait for Child"<<endl;
	
	
		int status;
		pid_t pid2;
		/*
		 * Parent blocks here until child finishes. Returnval gives the
		 * completion status of child (child's return value) and pid2
		 * gets the completing child's ID
		 */
		
		pid2 = wait(&status);	

		cout<<"Child "<<pid2<<" Finished with status "<<status<<endl;
		cout<<"\nParent Finishing Execution, Number = "<<number<<endl;
		
		return 0;
	}
	if (pid == 0) {	//pid variable gets 0 for child
		cout<<"Child Process: ID "<<getpid()<<" Number = "<<number<<endl;

		number = 10;//Child's copy of number (in child's address space)
		cout<<"New Value for Number is "<<number<<" Child Exiting !!!\n";
		
		return 0;
	}
}


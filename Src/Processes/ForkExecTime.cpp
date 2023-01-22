///Builds:	g++ ~/Codes/Src/Processes/ForkExecTime.cpp -o ~/Codes/Output/ForkTime
///Runs:	~/Codes/Output/ForkTime

/***********************************************************************
 * Authors: Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 * This program is an extension to ForkSimple.cpp. Here, Parent process 
 * forks a child, which in return loads a totaly different process to 
 * its address space. In this example, we load the simple date process.
 * Its binary file is located at /bin/date
 * 
 * Important Functions:
 * fork:	Creates a child process. Two processes (parent and child) 
 * 			start executing after this line
 * wait:	Stops execution of parent process, until child has 
 * 			returned. Parent can also get child's return status (success
 * 			failure etc) and id to decide its further execution 
 * exec		exec has many variants, which can be called according to the 
 * 			application needs. It replaces the caller process with the
 * 			process binaries specified in the exec call
 ***********************************************************************/

#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

	pid_t pid;
	pid = fork();	//Forks a child process

	if (pid < 0) {	//Fork fails
		cout<<"\nProcess Creation Failed\n";
	}

	if (pid > 0) {	//Parent process
		cout<<"Parent Process: ID "<<getpid()<<" Child ID "<<pid<<endl;		
		cout<<"Parent Process Going to Wait for The Child"<<endl;
		
		wait(NULL);		//Parent blocks until child exits
	
		cout<<"Parent Process Finishing Execution\n"<<endl;
	}

	if (pid == 0) {	//Child Process
		cout<<"Child Process: ID "<<getpid()<<" Parent "<<getppid()<<endl;
		cout<<"Child Calling EXEC, loading a new process"<<endl;

		//Replaces child with new process (date in this example)
		execl("/bin/date", "date", 0, 0);	
		
		//these lines execute only if exec fails		
		perror("exec failure");
	}
}


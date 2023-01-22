///Builds:	g++ ~/Codes/Src/First.cpp -o ~/Codes/Output/First
///Runs:	~/Codes/Output/First 2 6 9 4 6 1 5

/********************************************************************
 * Authors Dr Ali Hassan, Dr Muhammad Umar Farooq
 *
 ********************************************************************/

#include<stdio.h>

int main(int argc, char * argv []) {

    printf( "argc = %d\n", argc );
    for( int i = 0; i < argc; ++i ) {
        printf( "argv[ %d ] = %s\n", i, argv[ i ] );
    }

	return 0;
}

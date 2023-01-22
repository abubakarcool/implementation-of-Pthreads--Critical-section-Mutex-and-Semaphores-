# implementation of Pthreads in Linux System
 

#1. Hellow World Progam 
 g++ HelloPrint.cpp -lpthread -o Output/HelloThread
 ./Output/HelloThread

#2. Matrix Vector Multiplication
 g++ HelloPrint.cpp -lpthread -o Output/MatrixMul
 ./Output/MatrixMul

Learning critical section
#3. Calculating value of Pi
 g++ HelloPrint.cpp -lpthread -o Output/Pi
 ./Output/Pi

#4. Estimating Pi using Mutexes
 g++ HelloPrint.cpp -lpthread -o Output/PiSafe
 ./Output/PiSafe

Learning Semaphores
#5. Producer Consumer Problem
 g++ HelloPrint.cpp -lpthread -o Output/ProducerConsumer
 ./Output/ProducerConsumer

Learning Processes Fork and Exec
#6. Simple Fork Example
 g++ HelloPrint.cpp -lpthread -o Output/ForkSimple
 ./Output/ForkSimple

#7. Simple Exec Example
 g++ HelloPrint.cpp -lpthread -o Output/ForkTime
 ./Output/ForkTime

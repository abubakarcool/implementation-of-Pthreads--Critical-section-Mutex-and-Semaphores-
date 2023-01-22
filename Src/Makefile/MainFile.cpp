#include <iostream>
#include <SomeFunction.h>

using namespace std;
int main() {
  int num1, num2, result;

  cout<<"Please Enter First Number  : ";
  cin>>num1;
  cout<<"Please Enter Second Number : ";
  cin>>num2;

  /* Here we call a function find_sum defined in 
   * some other file, named SomeFunction.cpp. 
   * SomeFunction.h is the header include file */
   
  result = find_sum(num1, num2);
  cout<<"The Result is : "<<result<<endl;
  return(0);
}


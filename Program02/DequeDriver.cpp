#include "DequeArray.h"
#include "QueueDeque.h"
#include "StackDeque.h"
#include <iostream>

using namespace std;

int main()
{
  DequeArray<int>* test = new DequeArray<int>();

  cout << test->isEmpty() << endl;
  cout << test->size() << endl;

  cout << test->peek() << endl;
  cout << test->peekDeque() << endl;

  test->dequeue();
  test->dequeueAll();
  test->dequeueDeque();

  int* var1 = new int[4];
  var1[0] = 15;
  int* var2 = new int[4];
  var2[0] = 96;

  test->enqueue(var1);
  cout << test->dequeue()[0] << endl;

  test->dequeue();
  for(int i = 0;i < 7;i++)
  {
  test->enqueue(var1);
  test->enqueue(var2);
  }

  test->enqueueDeque(var2);
 
  cout <<"the real-est of tests" <<endl; 

  for(int i = 0;i < 10;i++)
  {
  cout << test->dequeue()[0] << endl;
  }

  cout << test->size() << endl;
  cout << test->dequeueDeque()[0] << endl;
  cout << test->size() << endl;

  test->~DequeArray();
  delete test;
  delete[] var1;
  delete[] var2;
  

  cout <<"gg no-re"<< endl;
  return 0;
}
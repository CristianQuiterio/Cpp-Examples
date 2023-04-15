#if !defined STACKDEQUE_H
#define STACKDEQUE_H

#include "DequeArray.h"

template < class T >
class StackDeque
{

   private:
      DequeArray<T>* stack;

   public:
      StackDeque();
      ~StackDeque();

      bool isEmpty();
      int size();
      void popAll();

      T* pop();
      void push(T* item);
      T* peek();

};

template < class T >
StackDeque<T>::StackDeque()
{
   stack = new DequeArray<T>();
}

template < class T >
StackDeque<T>::~StackDeque()
{
   delete stack;
}

template < class T >
bool StackDeque<T>::isEmpty()
{
   return (size() == 0);
}

template < class T >
int StackDeque<T>::size()
{
   return stack->size();
}

template < class T >
T* StackDeque<T>::peek()
{
   T* item = NULL;
   if (!isEmpty()) 
   {  
      item = stack->peek();
   }
   return item;
}

template < class T >
void StackDeque<T>::push(T* item)
{
   stack->enqueueDeque(item);
}

template < class T >
T* StackDeque<T>::pop()
{
   T* item = NULL;
   if (!isEmpty()) 
   {  
      item = stack->dequeue();
   }
   return item;
}

template < class T >
void StackDeque<T>::popAll()
{
   stack->dequeueAll();
}

#endif
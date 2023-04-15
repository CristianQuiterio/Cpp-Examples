#if !defined (QUEUEDEQUE_H)
#define QUEUEDEQUE_H

#include "DequeArray.h"

template < class T >
class QueueDeque
{

   private:
      DequeArray<T>* queuet; 

   public:
      QueueDeque();
      ~QueueDeque();

      bool isEmpty();
      int size();
      void dequeueAll();

      T* peek();
      void enqueue(T* item);
      T* dequeue();
};

template < class T >
QueueDeque<T>::QueueDeque() 
{
   queuet = new DequeArray<T>();
}  

template < class T >
QueueDeque<T>::~QueueDeque() 
{
   delete queuet;
} 

template < class T >
bool QueueDeque<T>::isEmpty() 
{
   return (queuet->size() == 0);
}  

template < class T >
int QueueDeque<T>::size()
{
   return queuet->size();
}

template < class T >
void QueueDeque<T>::dequeueAll() 
{
   queuet->dequeueAll();
} 

template < class T >
T* QueueDeque<T>::peek()
{
   T* item = NULL;
   if (!isEmpty())
   {  
      item = queuet->peek();
   }
   return item;
} 

template < class T >
void QueueDeque<T>::enqueue(T* item)
{
   queuet->enqueue(item);
} 

template < class T >
T* QueueDeque<T>::dequeue() 
{
   T* item = NULL;
   if (!isEmpty()) 
   {
      item = queuet->dequeue();
   }
   return item;
} 

#endif
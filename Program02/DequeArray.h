#if !defined NULL
#define NULL 0
#endif

#if !defined (DEQUEARRAY_H)
#define DEQUEARRAY_H

template < class T >
class DequeArray
{

   private:
      int max_queue;
      T** items;
      int front;
      int back;
      int sz;

      void arrayResize(int new_size);

   public:
      DequeArray();
      ~DequeArray();

      bool isEmpty();
      int size();
      void dequeueAll();

      T* peek();
      void enqueue(T* item);
      T* dequeue();
  
      T* peekDeque();
      void enqueueDeque(T* item);
      T* dequeueDeque();

};

template < class T >
void DequeArray<T>::arrayResize(int new_size)
{
   T** temp = new T*[new_size];
   int j = front;

   for (int i = 0; i < sz; i++)
   {
      temp[i] = items[j];
      j++;
      if (j == max_queue)
      {
         j = 0;
      }
   }

   front = 0;
   back = sz - 1;
   max_queue = new_size;

   delete[] items;
   items = temp;
}

template < class T >
DequeArray<T>::DequeArray() 
{
   max_queue = 5;
   items = new T*[max_queue];  
   front = 0;
   back = max_queue - 1;
   sz = 0;
}  

template < class T >
DequeArray<T>::~DequeArray() 
{
   delete[] items;
} 

template < class T >
bool DequeArray<T>::isEmpty() 
{
   return sz == 0;
}  

template < class T >
int DequeArray<T>::size()
{
   return sz;
}

template < class T >
void DequeArray<T>::dequeueAll() 
{
   delete[] items;

   max_queue = 2;
   items = new T*[max_queue];  
   front = 0;
   back = max_queue - 1;
   sz = 0;
} 

template < class T >
T* DequeArray<T>::peek()
{
   T* item = NULL;
   if (!isEmpty()) 
   {  
      item = items[front];
   }
   return item; 
} 

template < class T >
void DequeArray<T>::enqueue(T* item)
{
   if (sz == max_queue)
   {
      arrayResize(2*max_queue);
   }

   back++;
   if (back == max_queue)
   {
      back = 0;
   }

   items[back] = item;
   sz++;
}

template < class T >
T* DequeArray<T>::dequeue() 
{
   T* item = NULL;

   if (!isEmpty()) 
   {
      item = items[front];
      items[front] = NULL;
      front = front + 1;

      if (front == max_queue)
      {
         front = 0;
      }
      sz--;
   }

   return item; 
}

template < class T >
T* DequeArray<T>::peekDeque()
{
   T* item = NULL;
   if (!isEmpty()) 
   {  
      item = items[back];
   }
   return item; 
}

template < class T >
void DequeArray<T>::enqueueDeque(T* item)
{
   if (sz == max_queue)
   {
      arrayResize(2*max_queue);
   }

   front--;
   if (front == -1)
   {
      front = max_queue - 1;
   }

   items[front] = item;

   sz++;
}

template < class T >
T* DequeArray<T>::dequeueDeque()
{
   T* item = NULL;

   if (!isEmpty()) 
   {
      item = items[back];
      items[back] = NULL;
      back = back--;

      if (back == -1)
      {
         back = max_queue;
      }
      sz--;
   }

   return item; 
}

#endif
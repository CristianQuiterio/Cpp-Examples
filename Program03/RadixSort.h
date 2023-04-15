#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;

//RadixSort is a class designed to sort items independent of each other, based on ASCII placement
//Duplicate items will be in FIFO order. Use when sorting large amounts
//Requires assortment be in one of two orders: Ascending, or Descending (based on ASCII)

template < class T >
class RadixSort
{
   private:
  //Sorts a queue of items in ascending order. Recursively calls itself to sort a queue of items. 
    //Preconditions
      //requires the bin to be changed, therefore, bin passed in will be used. Make a separate bin if needed to use unsorted bin elsewhere
      //needs number of characters to sort to, must be greater than zero, character amount should not exceed largest amount of characters of any of the items in the array being passed in
      //along with the current character it is using. to sort by the first character, insert a 1 for current character
      //also requires the compare function of the type of class being passed in
    //Postconditions
      //does not return andything, but does sort the queue of items passed in into ascending order.
     static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));


  //Sorts an Array of items into ascending order. Utilizes bins and ASCII comparisons to determine placement
    //Preconditions
      //requires the sort array to be changed, therefore, array passed in will be used. Make a separate array if needed to use the unsorted array elsewhere
      //needs number of characters to sort to (n), must be greater than zero, character amount should not exceed largest amount of characters of any of the items in the array being passed in
      //along with the number of items, beginning with one, to sort to from the passed in array.
      //also requires the compare function of the type of class being passed in
    //Postconditions
      //does not return andything, but does sort the array of items passed in into ascending order.
     static void radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 1

  //Sorts an Array of items into Descending order. Utilizes ASCII comparisons to determine placement
    //Preconditions
      //requires the sort array to be changed, therefore, array passed in will be used. Make a separate array if needed to use the unsorted array elsewhere
      //needs number of characters to sort to (n), must be greater than zero, character amount should not exceed largest amount of characters of any of the items in the array being passed in
      //along with the number of items, beginning with one, to sort to from the passed in array.
      //also requires the compare function of the type of class being passed in
    //Postconditions
      //does not return andything, but does sort the array of items passed in into descending order.
     static void radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 2
 
   public:

  //Sorts and Array of items into either ascending order or descending order, based on bool passed in. Utilizes bins and ASCII comparisons to determine placement
    //Preconditions
      //requires the sort array to be changed, therefore, array passed in will be used. Make a separate array if needed to use the unsorted array elsewhere
      //needs number of characters to sort to (n), must be greater than zero, character amount should not exceed largest amount of characters of any of the items in the array being passed in
      //along with the number of items, beginning with one, to sort to from the passed in array.
      //
      //also requires the compare function of the type of class being passed in
    //Postconditions
      //returns the array of items passed in, but sorted either into ascending order or descending order based on bool specified.
     static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
   //DO THIS

   if(asc)
   {
      radixSortAsc(unsorted, num_to_sort, num_chars, getRadixChar);
   }
   else
   {
      radixSortDesc(unsorted, num_to_sort, num_chars, getRadixChar);
   }

  return unsorted;
}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS

   QueueLinked<T>* bigBin = new QueueLinked<T>[n];  

   for (int i = 0; i < n; i++)
   {
      bigBin->enqueue(sort[i]);
   }

   binSort(bigBin, 1, num_chars, getRadixChar);

   for (int i = 0; i < n; i++)
   {
      sort[i] = bigBin->dequeue();
   }

   delete[] bigBin;
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
if( (!bin->isEmpty()) && (bin->size() > 1) && (!(curr_char > num_chars)) )
{

   int num_queues = 37;
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

   for (int i = 0; i < num_queues; i++)
   {
      bins[i] = new QueueLinked<T>();
   }


   for (int k = 0; !bin->isEmpty() ; k++)
   {
      int binLoc = 0;
      char charcomp = (*getRadixChar) (bin->peek(), curr_char);

      if((charcomp >= 48) && (charcomp <= 57))
      {
         binLoc = charcomp - 47;
      }
      else if( ( (charcomp >= 65) && (charcomp <= 90) ) || ( (charcomp >= 97) && (charcomp <= 122) ) )
      {
         if((charcomp >= 65) && (charcomp <= 90))
         {
            charcomp = charcomp + 32;
         }

         binLoc = charcomp - 86;
      }
      else if(charcomp == 32)
      {
         binLoc = 0;
      }

      T* item = bin->dequeue();
      bins[binLoc]->enqueue(item);
   }

   if(!(curr_char > num_chars))
   {
      for (int i = 0; i < num_queues; i++)
      {
         if ((!bins[i]->isEmpty()) && (bins[i]->size() > 1)) 
         {
            binSort(bins[i],(curr_char + 1), num_chars, getRadixChar);
         }
      }
   }

   for(int i = 0; i < num_queues; i++)
   {
       while(!bins[i]->isEmpty())
         {
            bin->enqueue(bins[i]->dequeue());
         }
   }

   for (int i = 0; i < num_queues; i++) 
   {
      delete bins[i];
   }

   delete[] bins;
}
}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   int num_queues = 37;  //covers letters and digits
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

   //must instantiate each of the queues
   for (int i = 0; i < num_queues; i++)
   {
      bins[i] = new QueueLinked<T>();
   }

   for (int i = num_chars; i > 0; i--)
   {
      for (int k = 0; k < n; k++)
      {
         int binLoc = 0;
         char charcomp = (*getRadixChar) (sort[k], i);

         if((charcomp >= 48) && (charcomp <= 57))
         {
            binLoc = charcomp - 47;
         }
         else if( ( (charcomp >= 65) && (charcomp <= 90) ) || ( (charcomp >= 97) && (charcomp <= 122) ) )
         {
            if((charcomp >= 65) && (charcomp <= 90))
            {
               charcomp = charcomp + 32;
            }

            binLoc = charcomp - 86;
         }
         else if(charcomp == 32)
         {
            binLoc = 0;
         }

         bins[num_queues-1-binLoc]->enqueue(sort[k]);
      }

      int sortNum = 0;
      for (int j = 0; j < num_queues; j++)
      {
         while(!bins[j]->isEmpty())
         {
            sort[sortNum] = bins[j]->dequeue();
            sortNum++;
         }
      }
   }

   for (int i = 0; i < num_queues; i++) 
   {
      delete bins[i];
   }

   delete[] bins;
}

#endif

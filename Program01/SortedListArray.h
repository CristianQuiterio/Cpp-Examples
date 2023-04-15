#if !defined SORTED_LIST_ARRAY
#define SORTED_LIST_ARRAY

#include "ListArrayIterator.h"
#include "Text.h"


namespace CSC2110
{
template < class T >
class SortedListArray
{
  Private:
    T** items;
    int size;
    int maxSize;

    void arrayResize(int newMaxSize);

  Public:
    SortedListArray();
    ~sortedListArray();

    bool isEmpty()
    int size()
    T* get(String* search_key)
    void add(T* item)
    void remove(String* search_key)
    ListArrayIterator<T>* iterator()

};

template < class T >
SortedListArray::SortedListArray



}
#endif
#if !defined (PQAVL_H)
#define PQAVL_H

#include "AVLTree.h"

/*
This is a class designed to use priority queues to quickly insert and remove items. Use this
when you want to quickly sort items, and need either the largest or smallest item first.
*/


template < class T >
class PQAVL
{
   private:
      AVLTree<T>* avlTree;

   public:
/*
Pre: requires boolean to determine if the user wants a priority queue with a minimun, or one with a maximum.
     also needs the search and compare functions of the class you are using.
Post:creates a priority queue AVL Tree that can store and call items.
*/
       PQAVL(bool min_or_max, int (*compare_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));

/*
Pre: do not call if already deleted
Post:destroys the PQAVL. will lose all information stoored in PQ
*/
      ~PQAVL();

/*
Pre: 
Post:call to see if PQ is empty or not, returns a 1 if it is empty, and a 0 if it is not
*/
      bool pqIsEmpty();
/*
Pre: do not insert null. requires a data type to be turned in.
Post:adds an item to the PQ
*/
      void pqInsert(T* item);
/*
Pre: do not call if the PQ is empty.
Post:removes either the minimum value or maximum value item in the pq
*/
      T* pqRemove();
};

template < class T >
PQAVL<T>::PQAVL(bool min_or_max, int (*compare_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
    avlTree = new AVLTree<T>(compare_items, comp_keys, min_or_max, 1, 0);
}

template < class T >
PQAVL<T>::~PQAVL()
{
   delete avlTree;
}

template < class T >
bool PQAVL<T>::pqIsEmpty()
{
   return avlTree->isEmpty();
}

template < class T >
void PQAVL<T>::pqInsert(T* item)
{
   avlTree->insert(item);
}

template < class T >
T* PQAVL<T>::pqRemove()
{
   return avlTree->remove();
}

#endif
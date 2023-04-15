#if !defined (HEAPSKEW_H)
#define HEAPSKEW_H

#include "BinaryTree.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      virtual ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
   //DO THIS
		if (left->isEmpty())
		return right;
	else if (right->isEmpty())
		return left;
	else if (compare_items (left->getItem(), right->getItem()) > 0)     // left is smaller than right
		return merge(right, left);
	
	BinaryTree<T>* LL = left->detachLeftSubtree();
	BinaryTree<T>* LR = right->detachRightSubtree();
	
	Left->getRight()->attachRightSubtree(LL);
	
	if (LR == NULL)
	{
		left->attachLeftSubtree(right);
		return left;
	}
	else
	{
		BinaryTree<T>* subtree = merge(LR, right);
		left->attachLeftSubtree(subtree);
		return left;
	}










}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)

   BinaryTree<T>* itemTree = new BinaryTree(item);
   bt = this->merge(bt, itemTree);
   sze++;
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)

   T* result = bt->getRootItem();

   BinaryTree<T>* leftSub = bt->detachLeftSubtree();
   BinaryTree<T>* rightSub = bt->detachRightSubtree();

   bt = this->merge(leftSub, rightSub);
   
   sze--;
   return result;
}

template < class T >
void HeapSkew<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   bt->draw(cr, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif

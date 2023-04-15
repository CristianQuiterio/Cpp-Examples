#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "Drawable.h"
#include "AVLTreeIterator.h"
#include "Line.h"

#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

/*
This is a Binary Search Tree that organizes itself in such a way that all data 
is in realtively close positioning, making most of its operations order (logn).
Use this when you would like to be able to store data in a given order, and need 
to get any piece of data out relatively quickly.
*/


template < class T >
class AVLTree : public Drawable
{
   
   private:
      AVLTreeNode<T>* root;

      bool avlFlag;
      int sze;

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      void setRootNode(AVLTreeNode<T>* tNode); //you can get by without using these methods, refer to root directly
      AVLTreeNode<T>* getRootNode();

      int getHeight(AVLTreeNode<T>* tNode);  //from lab
      bool isBalanced(AVLTreeNode<T>* tNode);

      void destroyItem(AVLTreeNode<T>* tNode);
      void destroy();

      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);

      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);

      //write and use methods to do each of the four rotations (SR, SL, DLR, DRL)
      AVLTreeNode<T>* singleRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* singleLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DoubleRightLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DoubleLeftRight(AVLTreeNode<T>* tNode);


      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);

      virtual void drawRec(AVLTreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr);

   public:

  //Preconditions:Constructor for the AVLTree. requires both the compare and search
    //functions of the class being used
  //Postconditions:Creates an AVLTree that data can be stored in.
      AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));

  //Preconditions:Use only when you are completely done with the AVLTree, as it will
    //destroy everything in relation to it
  //Postconditions:Will not be able to access AVLTree anymore, but all data will be deleted
      ~AVLTree();

  //Preconditions:Use to obtain the number of elements in the AVLTree
  //Postconditions:Returns an integer with the size
      int size();
  //Preconditions:Use to insert an item into the Tree. Item will be placed in order based on 
    //compare function passed into constructor
  //Postconditions:Does not return anything, but places the item into the tree
      void insert(T* item);
  //Preconditions:Use to retrieve an item from the tree. Do not pass in Null.
  //Postconditions:If item is found, it will be returned.
      T* retrieve(String* sk);
  //Preconditions:Use to check if there is anything in the tree.
  //Postconditions:If number of elements in the tree is zero, it returns true. otherwise, returns false
      bool isEmpty();
  //Preconditions:Do not use if no elements have been passed in.
  //Postconditions:Retrieves the item at the root, assuming there is a value there.
      T* getRootItem();
  //Preconditions:Creates an iterator that will loop over the elements
  //Postconditions:
      AVLTreeIterator<T>* iterator();
  //Preconditions:
  //Postconditions:Obtains the height of the Tree
      int getHeight();
  //Preconditions:
  //Postconditions:Checks to see if the ENTIRE tree is balances
      bool isBalanced();

      void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item)
{
   AVLTreeNode<T>* subtree;

   if (tNode == NULL)
   { 
      sze++;
      return new AVLTreeNode<T>(item);
   }

   T* node_items = tNode->getItem();
   int comp = (*compare_items) (item, node_items);
   bool sideAdded = FALSE;
   if (comp == 0)
   {
      return tNode;
   }
   else if (comp < 0)
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
      sideAdded = TRUE;
   }
   else
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);   
   }

   if (avlFlag)
   {

      AVL tNodebalance = tNode->getBalanceFactor();

      if(sideAdded)
      {
         if (tNodebalance == RIGHT_HEAVY)
         {
            tNode->setBalanceFactor(BALANCED);
            avlFlag = FALSE;
         }
         else if (tNodebalance == BALANCED)
         {
            tNode->setBalanceFactor(LEFT_HEAVY);
         }
         else
         {
            tNode->setBalanceFactor(LEFT_UNBALANCED);
            tNode = avlFixAddLeft(tNode);
         }
      }
      else
      {
         if (tNodebalance == LEFT_HEAVY)
         {
            tNode->setBalanceFactor(BALANCED);
            avlFlag = FALSE;
         }
         else if (tNodebalance == BALANCED)
         {
            tNode->setBalanceFactor(RIGHT_HEAVY);
         }
         else
         {
            tNode->setBalanceFactor(RIGHT_UNBALANCED);
            tNode = avlFixAddRight(tNode);
         }
      }
   }
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
   if (tNode->getLeft()->getBalanceFactor() == RIGHT_HEAVY)
   {
      if (tNode->getLeft()->getRight()->getBalanceFactor() == BALANCED)
      {
         tNode->getLeft()->getRight()->setBalanceFactor(BALANCED);
         tNode->getLeft()->setBalanceFactor(BALANCED);
         tNode->setBalanceFactor(BALANCED);
         avlFlag = FALSE;
      }
      else if (tNode->getLeft()->getRight()->getBalanceFactor() == RIGHT_HEAVY)
      {
         tNode->getLeft()->getRight()->setBalanceFactor(BALANCED);
         tNode->getLeft()->setBalanceFactor(LEFT_HEAVY);
         tNode->setBalanceFactor(BALANCED);
         avlFlag = FALSE;
      }
      else
      {
         tNode->getLeft()->getRight()->setBalanceFactor(BALANCED);
         tNode->getLeft()->setBalanceFactor(BALANCED);
         tNode->setBalanceFactor(RIGHT_HEAVY);
      }

      return DoubleLeftRight(tNode);
   }
   else
   {
      tNode->setBalanceFactor(BALANCED);
      tNode->getLeft()->setBalanceFactor(BALANCED);
      avlFlag = FALSE;
      return singleRight(tNode);
   }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
   if (tNode->getRight()->getBalanceFactor() == LEFT_HEAVY)
   {
      if (tNode->getRight()->getLeft()->getBalanceFactor() == BALANCED)
      {
         tNode->getRight()->getLeft()->setBalanceFactor(BALANCED);
         tNode->getRight()->setBalanceFactor(BALANCED);
         tNode->setBalanceFactor(BALANCED);
         avlFlag = FALSE;
      }
      else if (tNode->getRight()->getLeft()->getBalanceFactor() == LEFT_HEAVY)
      {
         tNode->getRight()->getLeft()->setBalanceFactor(BALANCED);
         tNode->getRight()->setBalanceFactor(RIGHT_HEAVY);
         tNode->setBalanceFactor(BALANCED);
         avlFlag = FALSE;
      }
      else
      {
         tNode->getRight()->getLeft()->setBalanceFactor(BALANCED);
         tNode->getRight()->setBalanceFactor(BALANCED);
         tNode->setBalanceFactor(LEFT_HEAVY);
      }
      return DoubleRightLeft(tNode);
   }
   else
   {
      tNode->setBalanceFactor(BALANCED);
      tNode->getRight()->setBalanceFactor(BALANCED);
      avlFlag = FALSE;
      return singleLeft(tNode);
   }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::singleRight(AVLTreeNode<T>* tNode)
{
   return rotateRight(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::singleLeft(AVLTreeNode<T>* tNode)
{
   return rotateLeft(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DoubleLeftRight(AVLTreeNode<T>* tNode)
{
   tNode->setLeft(rotateLeft(tNode->getLeft()));
   return rotateRight(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DoubleRightLeft(AVLTreeNode<T>* tNode)
{
   tNode->setRight(rotateRight(tNode->getRight()));
   return rotateLeft(tNode);
}


template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* tNodeLeft = tNode->getLeft();
   tNode->setLeft(tNodeLeft->getRight());
   tNodeLeft->setRight(tNode);
   return tNodeLeft;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* tNodeRight = tNode->getRight();
   tNode->setRight(tNodeRight->getLeft());
   tNodeRight->setLeft(tNode);
   return tNodeRight;
}

template < class T>
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
   if(tNode != NULL)
   {
	int left = 0;
        int right = 0;
	
	right = getHeight(tNode->getRight());
	left = getHeight(tNode->getLeft());

	if(left < right)
        {
		return right + 1;
        }
	else
	{
		return left + 1;
	}
   }

   int baseCase = 0;
   return baseCase;
}

template < class T>
bool AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
   int leftH, rightH;
   bool left, right;
	if(!(tNode==NULL))
	{
		right = isBalanced(tNode->getRight());
		left = isBalanced(tNode->getLeft());
		if(right && left)
		{
			leftH= getHeight(tNode->getLeft());
			rightH= getHeight(tNode->getRight());
			if(rightH == leftH)
                        {
				return true;
                        }
			else
                        {
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}	
}

template < class T>
bool AVLTree<T>::isBalanced()
{
	bool b = isBalanced(root);
	return b;
}

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{
   root = tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
   return root;
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
void AVLTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
AVLTree<T>::AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   root = NULL;
   sze = 0;
   avlFlag = false;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
AVLTree<T>::~AVLTree()
{
   destroy();
}

template < class T >
int AVLTree<T>::size()
{
   return sze;
}

template < class T >
void AVLTree<T>::insert(T* item)
{
   avlFlag = TRUE;
   root = insertItem(root, item);
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
   AVLTreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_items = tNode->getItem();
      int comp = (*compare_keys) (sk, node_items);

      if (comp == 0)
      {
         return node_items;
      }
      else if (comp < 0)
      {
         tNode = tNode->getLeft();
      }
      else
      {
         tNode = tNode->getRight();
      }
   }
}

template < class T >
bool AVLTree<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
T* AVLTree<T>::getRootItem()
{
   T* rootItem = root->getItem();
   return rootItem;
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
   return new AVLTreeIterator<T>(root);
}

template < class T>
int AVLTree<T>::getHeight()
{
   int leHeight = getHeight(root);
   return leHeight;
}

//the below GUI-related methods have been completed for you

template < class T >
void AVLTree<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), cr, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, Cairo::RefPtr<Cairo::Context> cr, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(cr, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), cr, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), cr, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(cr, x_curr, y_curr);
   }
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif

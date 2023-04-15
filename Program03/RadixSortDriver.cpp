#include "RadixSort.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "Text.h"
using CSC2110::String;
#include "Keyboard.h"
using CSC2110::Keyboard;


#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* list = CD::readCDs("cds.txt");
   int size = list->size();

   CD** cds = new CD*[size];

   ListArrayIterator<CD>* iter = list->iterator();
   int count = 0;
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      cds[count] = cd;
      count++;
   }
   delete iter;

   //DO THIS
   //test both radix sort methods using the cds array

   Keyboard* kb ;
   int num_to_sort = kb->getValidatedInt("Please enter the number of items to sort:",1,size);
   bool asc = kb->getValidatedInt("Would you like those sorted in (1)Ascending or (0)Descending order? ",0,1);
   int num_chars = kb->Keyboard::getValidatedInt("Please enter the number of characters you would like to sort to:",1,size);

   cds = RadixSort<CD>::radixSort(cds,num_to_sort,num_chars,asc, &CD::getRadixChar);

   for(int i = 0; i < num_to_sort ; i++)
   {
      cds[i]->displayCD();
   }

   delete[] cds;

   deleteCDs(list);
   delete list;

   return 0;
}

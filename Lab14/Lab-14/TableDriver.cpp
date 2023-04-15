// github.com/Jrwilliams43/Lab-14

#include "TableSortedList.h"
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;
#include "Text.h"
using CSC2110::String;

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
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   TableSortedList<CD>* slt = new TableSortedList<CD>(&CD::compare_items, &CD::compare_keys);

   //DO THIS
   //thoroughly test your table


   ListArrayIterator<CD>* iter = cds->iterator();

   slt->tableInsert(iter->next());

   while(iter->hasNext())
   {
      slt->tableInsert(iter->next());
   }

   cout<<slt->tableSize()<<endl;
   cout<<slt->tableIsEmpty()<<endl;

   iter = cds->iterator();
   slt->tableInsert(iter->next());

   cout<<slt->tableSize()<<endl;
   cout<<slt->tableIsEmpty()<<endl;


   iter = cds->iterator();
   CD* cd;

   while(iter->hasNext())
   {
      cd = iter->next();
      slt->tableRetrieve(cd->getKey());
      slt->tableRemove(cd->getKey());
      slt->tableRetrieve(cd->getKey());
      slt->tableRemove(cd->getKey());
   }

   cout<<slt->tableSize()<<endl;
   cout<<slt->tableIsEmpty()<<endl;

   cout<<slt->tableRemove(cd->getKey())<<endl;

   cout<<slt->tableSize()<<endl;
   cout<<slt->tableIsEmpty()<<endl;

   deleteCDs(cds);
   delete iter;
   delete cds;
   delete slt;
   return 0;
}

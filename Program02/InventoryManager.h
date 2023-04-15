#if !defined INVENTORYMANAGER_H
#define INVENTORY_H

#include "StackDeque.h"
#include "QueueDeque.h"
#include "Widget.h"

//This class is used primarily for the storage and transactions of widgets, and allows items 
//to be logged as bought or sold to deetermine a profit for widgets.
//Allows for either Stack or Queue management.

class InventoryManager
{

   private:
      bool InvType;
      double profit;
      StackDeque<Widget>* stack;
      QueueDeque<Widget>* queue;

   public:

  //Create an Inventory Manager
    //Preconditions:
      //Requires a 0  or a 1
      //choice declares Stack or Queue
      //0 is for a Stack(LIFO), and 1 is for a Queue(FIFO)
    //Postconditions:
      //creates an InventoryManager class witht the following functions
      InventoryManager(bool choice);

  //Use to delete the InventoryManager
    //Postcondition:
      //Deletes all classes in the InventoryManager
      ~InventoryManager();

  //Use to add widgets to inventory
    //Preconditions:
      //the cost of each of the widgets bought
      //allows for entry of multiple widgets with the same price to be added at the same time.
      //widgets of same price are considered indistinguishable from other widgets of the same price directly next to them
    //Postconditions:
      //does not return anything
      //puts widgets into the inventory in the order you enter them in
      void buyWidgets(double cost, int numToBuy);

  //Gets total overall profit from all transactions
    //Postconditions:
      //uses the total amount of profit gained after all transactions
      //does not store previous transaction totals after a new transaction has occured
      double getTotalProfit();

  //Use to sell widgets and determine profit made on them
    //Preconditions:
      //if number to sell exceeds number in inventory, it will sell the remaining widgets and generate total based off of that
      //requires the price of the widgets sold, along with the number needed to sell
      //price should not exceed the value of a double
    //Postconditions:
      //returns the profit made from the transaction
      //does not retain knowledge of widgets sold past selling point, and knowledge of previos sales is not kept
      double sellWidgets(double price, int numToSell);
};



#endif
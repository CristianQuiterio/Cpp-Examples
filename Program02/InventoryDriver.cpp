#include "InventoryManager.h"
#include "Text.h"
using CSC2110::String;
#include "Keyboard.h"
using CSC2110::Keyboard;

#include <iostream>
#include <iomanip>
using namespace std;

int inventoryChoice()
{
   Keyboard* kb = Keyboard::getKeyboard();
   int inv_choice = kb->getValidatedInt("Are you using (0) LIFO or (1) FIFO inventory management? ", 0, 1);
   return inv_choice;
}

//DO THIS
//buy Widgets (check invalid input and reprompt if necessary)
void buyWidgets(InventoryManager* im)
{
  Keyboard* key = Keyboard::getKeyboard();
  int num = key->getValidatedInt("How many widgets would you like to buy?", 0, 1000000000);
  double cost = key->getValidatedDouble("What is the price of each Widget?", 0, 1000000000);
  im->buyWidgets(cost, num);
}

//DO THIS
//sell Widgets and return the profit (check invalid input and reprompt if necessary)
double sellWidgets(InventoryManager* im)
{
  Keyboard* key = Keyboard::getKeyboard();
  int num = key->getValidatedInt("How many widgets would you like to sell?", 0, 1000000000);
  double cost = key->getValidatedDouble("What is the price of each Widget?", 0, 1000000000);
  double sale = im->sellWidgets(cost, num);
  cout << "Your profit on this transaction is $" << sale << "." << endl;
  return sale;
}

bool mainMenu(InventoryManager* im)
{
   Keyboard* kb = Keyboard::getKeyboard();
   int menu_choice = kb->getValidatedInt("1. Buy Widgets \r\n2. Sell Widgets\r\n3. Quit\r\nWhat would you like to do? ", 1, 3);

   double profit = 0;

   if (menu_choice == 1)
   {
      buyWidgets(im);
      return 1;
   }
   else if(menu_choice == 2)
   {
      sellWidgets(im);
      return 1;
   }
   else 
   {
      return 0;
   }
}

int main()
{
   cout << setprecision(2) << fixed;

   int inv_choice = inventoryChoice();
   InventoryManager* im = new InventoryManager(inv_choice);

   bool ask = 1;
   while (ask)
   {
      ask = mainMenu(im);
   }

   double running_total = im->getTotalProfit();
   cout << "Your total profit for all transactions is $" << running_total << endl;

   delete im;
}
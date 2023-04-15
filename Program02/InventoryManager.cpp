#include "InventoryManager.h"
#include "Widget.h"
#include <iostream>
using namespace std;
InventoryManager::InventoryManager(bool choice)
{
  if(!choice)
  {
    stack = new StackDeque<Widget>();
  }
  else
  {
    queue = new QueueDeque<Widget>();
  }
  
  profit = 0;
  InvType = choice;
}

InventoryManager::~InventoryManager()
{
    if(!InvType)
  {
    delete stack;
  }
  else
  {
    delete queue;
  }
}


void InventoryManager::buyWidgets(double cost, int numToBuy)
{
  if(!InvType)
  {
    for(int i = 1; i <= numToBuy; i++)
    {
      Widget* widget = new Widget(cost);
      stack->push(widget);
    }
  }
  else
  {
    for(int i = 1; i <= numToBuy; i++)
    {
      Widget* widget = new Widget(cost);
      queue->enqueue(widget);
    }
  }
}

double InventoryManager::getTotalProfit()
{
  return profit;
}


double InventoryManager::sellWidgets(double price, int numToSell)
{
  double sale = 0;
  Widget* widgett;
  if(!InvType)
  {

    if(numToSell > stack->size())
    {
      numToSell = stack->size();
    }

    for(int i = 0; i < numToSell; i++)
    {
      widgett = stack->pop();
      sale = sale + price - widgett->getCost();
    }
  }
  else
  {

    if(numToSell > queue->size())
    {

      numToSell = queue->size();
    }

    for(int i = 1; i <= numToSell; i++)
    {
      widgett = queue->dequeue();
      sale = sale + price - widgett->getCost();
    }
  }

  profit = profit + sale;
  return sale;
}
























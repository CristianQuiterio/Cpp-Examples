#include "Widget.h"

Widget::Widget(double value)
{
   cost = value;
}

Widget::~Widget()
{
}

double Widget::getCost()
{
   return cost;
}
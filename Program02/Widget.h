#if !defined WIDGET_H
#define WIDGET_H

class Widget
{

   private:
      double cost;

   public:
      Widget(double value);
      ~Widget();

      double getCost();

};

#endif
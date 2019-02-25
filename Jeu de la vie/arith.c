#include "arith.h"

int min(int a, int b){ return (a < b)*a + (a >= b)*b;}

int reste_div(int a, int b)
{
     int reste = a;
     while (reste >= b || reste < 0)
     {
          if (reste < 0)
          {
               reste += b;
          }
          else
          {
               reste -= b;
          }
     }
     return reste;
}

#include "som_def.h"

int main()
{
  parameter p;
  p.depth = 5;
  p.map_x = 10;
  p.map_y = 30;

  init_networt(p);
  auto som = new Som(5, 7, 3);
  delete som;
  return 0;
}
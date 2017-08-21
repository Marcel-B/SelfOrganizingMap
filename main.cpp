#include "som_def.h"
#include <iostream>
using namespace std;

int main()
{
  // parameter p;
  // p.depth = 5;
  // p.map_x = 10;
  // p.map_y = 30;

  // init_networt(p);
  auto som = new Som(5, 7, 3);
  cout << "Init ready" << endl;
  for (size_t it = 0; it < 50; ++it)
    cout << som->learning_linear(it + 1) << endl;
  for (size_t it = 0; it < 50; ++it)
    cout << som->learning_inverse_of_time(it + 1) << endl;
  for (size_t it = 0; it < 50; ++it)
    cout << som->learing_power_series(it + 1) << endl;
  for (size_t i = 0; i < 3000; ++i)
    cout << som->neighbor_radius(i + 1) << endl;
  delete som;

  return 0;
}
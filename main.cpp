#include "som_def.h"
#include <iostream>
using namespace std;


int main()
{
  foo_bar("copy.csv");
  auto som = new Som(55, 99, 3);
  cout << "Init ready" << endl;
  for (size_t it = 0; it < 50; ++it)
    som->learning_linear(static_cast<unsigned long>(it) + 1);
  for (size_t it = 0; it < 50; ++it)
    som->learning_inverse_of_time(static_cast<unsigned long>(it) + 1);
  for (size_t it = 0; it < 50; ++it)
    som->learing_power_series(static_cast<unsigned long>(it) + 1);
  for (size_t i = 0; i < 3000; ++i)
    som->neighbor_radius(static_cast<unsigned long>(i) + 1);
  delete som;
  return 0;
}

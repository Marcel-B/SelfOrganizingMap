#include "som_def.h"
#include <iostream>
using namespace std;

int main()
{
  vector<vector<double>> scaled_data;
  foo_bar("copy.csv", scaled_data);
  size_t num_u = scaled_data[0].size();
  cout << num_u << endl;
  auto som = new Som(500, 590, num_u);
  som->set_train_data(scaled_data);
  scaled_data.clear();
  som->start_training();

  cout << "Init ready" << endl;
  for (size_t it = 0; it < 50; ++it)
    som->learning_inverse_of_time(static_cast<unsigned long>(it) + 1);
  for (size_t it = 0; it < 50; ++it)
    som->learing_power_series(static_cast<unsigned long>(it) + 1);
  delete som;
  return 0;
}

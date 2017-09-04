#include "som/som.hpp"
#include "infrastructure/inout.hpp"
#include "infrastructure/set.h"
#include "infrastructure/types.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
  for (size_t i = 0; i < argc; ++i)
    cout << argv[i] << endl;
  string validation_data = "test.set";
  vector<vector<double>> scaled_data;
  auto set = new com_b_velop::Set();

  com_b_velop::InOut::ImportData("test.csv", set);
  scaled_data.clear();
  auto split_set = set->SplitValues(30);

  // Erst mal wegspeichern
  delete split_set->SaveSet(validation_data.c_str());
  auto som = new com_b_velop::Som(1000, 600, set->cols);
  som->set_iteration_max(2);
  som->set_train_data(set)->StartTraining();
  auto tmp_set = com_b_velop::Set::OpenSet(validation_data.c_str());
  tmp_set->features = set->features;
  auto validation = som->Validation(tmp_set);
  auto valid_set = validation.valid_set;
  for (size_t i = 0; i < valid_set.size(); ++i)
  {
    cout << setw(8) << valid_set[i].d << " | BMU[" << valid_set[i].x << "][" << valid_set[i].y << "]" << endl;
    for (size_t j = 0; j < valid_set[i].out.size(); ++j)
    {
      cout << setw(8) << valid_set[i].out[j] << " | ";
    }
    cout << endl;
    for (size_t j = 0; j < valid_set[i].in.size(); ++j)
    {
      cout << setw(8) << valid_set[i].in[j] << " | ";
    }
    cout << endl
         << endl;
  }
  cout << "TestData: " << valid_set.size() << endl;
  cout << "Distance: " << validation.distance << endl;
  cout << "Init ready" << endl;

  delete som;
  return 0;
}

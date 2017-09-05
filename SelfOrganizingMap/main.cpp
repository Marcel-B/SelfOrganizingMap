#include "som.hpp"
#include "inout.h"
#include "set.h"
#include "types.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
  for (size_t i = 0; i < argc; ++i)
    cout << argv[i] << endl;
  string validation_data = "test.set";
  vector<vector<double>> scaled_data;
  auto set = new com_b_velop::Set();

  com_b_velop::InOut::ImportData("copy.csv", set);
  scaled_data.clear();
  auto split_set = set->SplitValues(30);

  // Erst mal wegspeichern
  delete split_set->SaveSet(validation_data.c_str());
  auto som = new com_b_velop::Som(70, 30, set->cols);
  som->set_iteration_max(2);
  som->set_train_data(set)->StartTraining();
  auto tmp_set = com_b_velop::Set::OpenSet(validation_data.c_str());
  tmp_set->features = set->features;
  auto validation = som->Validation(tmp_set);
  auto valid_set = validation.valid_set;

  ofstream ofs("table1.csv", ios::out);
  ofstream oofs("table2.csv");
  ofstream del ("delta.csv");
  stringstream strst;
  string tmp;
  int idx;
  ofs << set->features[0].name;
  oofs << set->features[0].name;
  del << set->features[0].name;
  for (size_t j = 1; j < valid_set[0].out.size(); ++j)
  {
    ofs << ';' << set->features[j].name;
    oofs << ';' << set->features[j].name;
    del << ';' << set->features[j].name;
  }
  ofs << endl;
  oofs << endl;
  del << endl;
  for (size_t i = 0; i < valid_set.size(); ++i)
  {
//    cout << setw(8) << valid_set[i].d << " | BMU[" << valid_set[i].x << "][" << valid_set[i].y << "]" << endl;
    tmp = to_string(valid_set[i].out[0]);
    idx = tmp.find('.');
    if(idx >= 0)
      tmp[idx] =  ',';
    tmp.erase ( tmp.find_last_not_of('0') + 1, std::string::npos );
    for (size_t j = 1; j < valid_set[i].out.size(); ++j)
    {
      tmp = to_string(valid_set[i].out[j]);
      idx = tmp.find('.');
      if(idx >= 0)
        tmp[idx] =  ',';
      tmp.erase ( tmp.find_last_not_of('0') + 1, std::string::npos );
      ofs << ';' << tmp;
    }
    ofs << endl;


    tmp = to_string(valid_set[i].in[0]);
    idx = tmp.find('.');
    if(idx >= 0)
      tmp[idx] =  ',';

    tmp.erase ( tmp.find_last_not_of('0') + 1, std::string::npos );

    oofs << tmp;
    for (size_t j = 1; j < valid_set[i].in.size(); ++j)
    {
      tmp = to_string(valid_set[i].in[j]);
      idx = tmp.find('.');
      if(idx >= 0)
        tmp[idx] =  ',';
      tmp.erase ( tmp.find_last_not_of('0') + 1, std::string::npos );
      oofs << ';' << tmp;
    }
    oofs <<  endl;

    tmp = to_string(valid_set[i].delta[0]);
    idx = tmp.find('.');
    if(idx >= 0)
      tmp[idx] =  ',';
    tmp.erase ( tmp.find_last_not_of('0') + 1, std::string::npos );

    del << tmp;
    for (size_t j = 1; j < valid_set[i].in.size(); ++j)
    {
      tmp = to_string(valid_set[i].delta[j]);
      idx = tmp.find('.');
      if(idx >= 0)
        tmp[idx] =  ',';
      tmp.erase ( tmp.find_last_not_of('0') + 1, std::string::npos );
      del << ';' << tmp;
    }
    del <<  endl;
  }
  del.close();
  oofs.close();
  ofs.close();

  cout << setw(22) << setfill(' ') << left << "Init ready" << endl;

  delete som;
  return 0;
}
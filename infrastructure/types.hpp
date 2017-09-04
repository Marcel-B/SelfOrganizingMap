#pragma once
#include <string>
#include <vector>

using namespace std;
namespace com_b_velop
{
/*
* Metainfo zu einer Spalte
*/

// void foo_bar(const char *source, vector<vector<double>> &out_scaled_data);
// vector<Merkmal> get_merkmal(const vector<vector<double>> &in_values, const vector<string> &in_header);
  struct Point
  {
    size_t x;
    size_t y;
    double dist;
  };
  struct ValidSet
  {
    size_t w;
    size_t x;
    size_t y;
    double d;
    vector<double> out;
    vector<double> in;
  };
  struct Validation
  {
    vector<ValidSet> valid_set;
    double distance;
  };
} // namespace com_b_velop

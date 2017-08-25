#pragma once
#include <string>
#include <vector>

using namespace std;
namespace b_velop
{
struct Merkmal
{
  string name;
  double max;
  double min;
};
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
struct SetInfo
{
  vector<Merkmal> merkmale;
};
struct Set
{
  double **values;
  size_t rows;
  size_t cols;
  SetInfo set_info;
  Set(){};
  Set(const vector<vector<double>> &in_values);
  Set *split_values(const unsigned short &in_percent);
  Set *init_values(const size_t &in_rows, const size_t &in_cols);
  Set *dealloc_values();
  ~Set();
  static Set *open_set(const char *in_source);
  Set *save_set(const char *in_destination);
};
}
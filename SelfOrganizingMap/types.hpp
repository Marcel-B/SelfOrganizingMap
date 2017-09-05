#pragma once
#include <string>
#include <vector>

using namespace std;
namespace com_b_velop
{
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
    vector<double> delta;
  };
  struct Validation
  {
    vector<ValidSet> valid_set;
    double distance;
  };
} // namespace com_b_velop

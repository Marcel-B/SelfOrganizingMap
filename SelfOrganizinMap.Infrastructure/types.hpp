#pragma once
#include <string>
#include <vector>

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
	  std::vector<double> out;
	  std::vector<double> in;
	  std::vector<double> delta;
  };
  struct Validation
  {
	  std::vector<ValidSet> valid_set;
    double distance;
  };
} // namespace com_b_velop

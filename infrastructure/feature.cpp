//
// Created by MarcelBenders on 04.09.2017.
//
#include "feature.h"
#include <string>
#include <sstream>
#include <iomanip>

std::string com_b_velop::Feature::ToString() const {
  std::stringstream sstream;
  sstream << std::setw(25) << std::left
          << this->name  << std::setw(12) << std::right
          << this->min << std::setw(12) << std::right
          << this->max;
  return sstream.str();
}
std::string com_b_velop::Feature::ToString(size_t width) const {
  std::stringstream sstream;
  sstream << std::setw(width) << std::left
          << this->name  << std::setw(12) << std::right
          << this->min << std::setw(12) << std::right
          << this->max;
  return sstream.str();
}
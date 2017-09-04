//
// Created by MarcelBenders on 04.09.2017.
//
#ifndef SOM_SETINFO_H
#define SOM_SETINFO_H
#include "feature.h"
#include <vector>
#include <string>

namespace com_b_velop{
  struct SetInfo
  {
    std::vector<Feature> features;
    void print() const;
    std::string ToString() const;
  };
} // namespace com_b_velop
#endif //SOM_SETINFO_H

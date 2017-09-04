//
// Created by MarcelBenders on 04.09.2017.
//

#ifndef SOM_FEATURE_H
#define SOM_FEATURE_H
#include <string>
#include <sstream>
namespace com_b_velop{
  struct Feature
  {
    std::string name;
    double max;
    double min;
    std::string ToString() const;
    std::string ToString(size_t width) const;
  };
}
#endif //SOM_FEATURE_H

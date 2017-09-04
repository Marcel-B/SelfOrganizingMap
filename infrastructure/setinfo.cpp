//
// Created by MarcelBenders on 04.09.2017.
//
#include "setinfo.h"
#include <iostream>

std::string com_b_velop::SetInfo::ToString() const {
  std::string ret("TestString");
  return ret;
}
void com_b_velop::SetInfo::print() const {
  for(size_t i = 0; i < this->features.size(); ++i){
    std::cout << this->features[i].ToString() << std::endl;
  }
}

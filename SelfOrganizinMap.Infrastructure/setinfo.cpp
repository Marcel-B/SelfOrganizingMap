//
// Created by MarcelBenders on 04.09.2017.
//
#include "setinfo.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace com_b_velop;

std::string SetInfo::ToString() const {
  std::stringstream strstream;
  strstream << "SetInfo" << std::endl;
  strstream << this->features.size() << " Features are stored" << std::endl;
  return strstream.str();
}
void SetInfo::Print() const {
  std::cout << this->ToString();
}

SetInfo SetInfo::SaveSetInfo(std::ofstream &stream) {
  this->features_size = this->features.size();
  stream.write(reinterpret_cast<char*>(&this->features_size), sizeof(this->features_size));
  for(size_t i = 0; i < this->features_size; ++i){
    std::string name = this->features[i].name;
    size_t name_size = name.size();
	  const auto cc = name.c_str();
    stream.write(reinterpret_cast<char*>(&name_size), sizeof(size_t));
    stream.write(cc, name_size);
    stream.write(reinterpret_cast<char*>(&this->features[i].min), sizeof(this->features[i].min));
    stream.write(reinterpret_cast<char*>(&this->features[i].max), sizeof(this->features[i].max));
  }
  return *this;
}

SetInfo SetInfo::OpenSetInfo(std::ifstream &stream) {
  SetInfo info;
  stream.read(reinterpret_cast<char*>(&info.features_size), sizeof(info.features_size));
  info.features.resize(info.features_size);
  for(size_t i = 0; i < info.features_size; ++i){
    size_t len = 0;
    stream.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    char* tp = new char[len + 1];
    stream.read(tp, len);
    tp[len] = '\0';
    info.features[i].name = tp;
    delete tp;
    stream.read(reinterpret_cast<char*>(&info.features[i].min), sizeof(info.features[i].min));
    stream.read(reinterpret_cast<char*>(&info.features[i].max), sizeof(info.features[i].max));
  }
  return info;
}


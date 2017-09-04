//
// Created by MarcelBenders on 04.09.2017.
//

#ifndef SOM_SET_H
#define SOM_SET_H

#include "setinfo.h"
namespace com_b_velop{
  struct Set : public SetInfo
  {
    double **values;
    size_t rows;
    size_t cols;
    Set(){};
    Set(const vector<vector<double>> &in_values);
    ~Set();
    Set *SetSet(const vector<vector<double>> &in_values);
    Set *SplitValues(const unsigned short &in_percent);
    Set *InitValues(const size_t &in_rows, const size_t &in_cols);
    Set *DeallocValues();
    static Set *OpenSet(const char *in_source);
    Set *SaveSet(const char *in_destination);
  };
} // namespace com_b_velop
#endif //SOM_SET_H

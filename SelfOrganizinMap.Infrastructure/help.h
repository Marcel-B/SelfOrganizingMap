//
// Created by marce on 03.09.2017.
//

#ifndef SOM_HELP_H
#define SOM_HELP_H
#include <time.h>
#include <string>

namespace com_b_velop {
  struct Help {
    static double ScaleValue(double x, double min, double max, double a, double b);
    tm* ParseTime(const std::string &in_time_string);
  };
} // namespace com_b_velop
#endif //SOM_HELP_H

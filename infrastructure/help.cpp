//
// Created by marce on 03.09.2017.
//
#include "help.h"

// a = unterer Zielwert, b = oberer Zielwert
double com_b_velop::Help::ScaleValue(double x, double min, double max, double a, double b){
  if (max - min == 0)
    return a;
  return x == 0 ? a : a + (b - a) * (x - min) / (max - min);
}
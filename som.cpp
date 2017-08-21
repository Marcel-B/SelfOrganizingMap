#include "som_def.h"
#include <stdlib.h>
#include <iostream>
#include <random>

using namespace std;

Som::Som(unsigned long x, unsigned long y, unsigned long z) : alpha(7),
                                                              iteration_max(5000),
                                                              neighbor_start(2)
{
  this->map_x = x;
  this->map_y = y;
  this->map_z = z;
  this->init();
  cout << "init rdy" << endl;
}

Som *Som::init()
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  this->map = static_cast<double ***>(malloc(sizeof(double **) * this->map_y));
  for (size_t row = 0; row < this->map_y; ++row)
  {
    this->map[row] = static_cast<double **>(malloc(sizeof(double *) * this->map_x));
    for (size_t col = 0; col < this->map_x; ++col)
    {
      this->map[row][col] = static_cast<double *>(malloc(sizeof(double) * this->map_z));
      for (size_t w = 0; w < this->map_z; ++w)
      {
        this->map[row][col][this->map_z] = dist(mt);
        //cout << this->map[row][col][this->map_z] << " ";
      }
      cout << endl;
    }
  }
  return this;
}

Som::~Som()
{
  cout << "kill" << endl;
  for (size_t row = 0; row < this->map_y; ++row)
  {
    for (size_t col = 0; col < this->map_x; ++col)
    {
      delete[] this->map[row][col];
    }
    delete[] this->map[row];
  }
  delete[] this->map;
  cout << "Deleted " << this << endl;
}
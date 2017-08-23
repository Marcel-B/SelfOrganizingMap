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
  init_map();
  cout << "init rdy" << endl;
}

Som *Som::init_map()
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  cout << "Eins" << endl;
  this->map = static_cast<double ***>(malloc(sizeof(double **) * this->map_y));
  try
  {
    for (size_t row = 0; row < this->map_y; ++row)
    {
      this->map[row] = static_cast<double **>(malloc(sizeof(double *) * this->map_x));
      for (size_t col = 0; col < this->map_x; ++col)
      {
        this->map[row][col] = static_cast<double *>(malloc(sizeof(double) * this->map_z));
        for (size_t w = 0; w < this->map_z; ++w)
        {
          this->map[row][col][w] = dist(mt);
        }
      }
    }
  }
  catch (...)
  {
    cout << "Malloc error" << endl;
  }
  cout << "Zwei" << endl;
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
  cout << "Map" << endl;
  delete[] this->map;
  cout << "Map2" << endl;
  for (size_t i = 0; i < this->train_data_size; ++i)
  {
    delete[] this->train_data[i];
  }
  cout << "train" << endl;
  delete[] this->train_data;
  cout << "train2" << endl;
  cout << "Deleted " << this << endl;
}

// Die Traingsdaten kopieren
Som *Som::set_train_data(const double **in_train_data, unsigned long size)
{
  this->train_data_size = size;
  for (size_t i = 0; i < size; ++i)
  {
    for (size_t w = 0; w < this->map_z; ++w)
    {
      this->train_data[i][w] = in_train_data[i][w];
    }
  }
  return this;
}

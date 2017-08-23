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
  init_alpha_values();
  init_radius();
  cout << "Initialization ready" << endl;
}
unsigned short Som::get_neighbor_radius(const size_t &iteration)
{
  return static_cast<unsigned short>(static_cast<double>(this->neighbor_start) * exp(-(static_cast<double>(iteration) / static_cast<double>(this->iteration_max))));
}
Som *Som::init_radius()
{
  this->neighbor_radius = static_cast<unsigned short *>(malloc(sizeof(unsigned short) * this->iteration_max));
  for (size_t iteration = 0; iteration < this->iteration_max; ++iteration)
    this->neighbor_radius[iteration] = get_neighbor_radius(iteration);
  cout << "Neighbor radius ready" << endl;
  return this;
}
Som *Som::init_map()
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
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
  cout << "Map ready" << endl;
  return this;
}

Som::~Som()
{
  cout << "Som deallocate process started" << endl;
  for (size_t row = 0; row < this->map_y; ++row)
  {
    for (size_t col = 0; col < this->map_x; ++col)
    {
      delete[] this->map[row][col];
    }
    delete[] this->map[row];
  }
  delete[] this->map;
  cout << "Map deleted" << endl;
  for (size_t i = 0; i < this->train_data_size; ++i)
  {
    delete[] this->train_data[i];
  }
  delete[] this->train_data;
  cout << "Train values deleted" << endl;

  delete[] this->alpha_values;
  cout << "Alpha values deleted" << endl;

  delete[] this->neighbor_radius;
  cout << "Neighbor radius deleted" << endl;
  cout << "Som deallocate process finished (" << this << ")" << endl;
}

// Die Traingsdaten kopieren
Som *Som::set_train_data(const vector<vector<double>> &in_train_data)
{
  this->train_data_size = in_train_data.size();
  this->train_data = static_cast<double **>(malloc(sizeof(double *) * this->train_data_size));
  for (size_t i = 0; i < this->train_data_size; ++i)
  {
    this->train_data[i] = static_cast<double *>(malloc(sizeof(double) * in_train_data[i].size()));
    for (size_t w = 0; w < in_train_data[i].size(); ++w)
    {
      this->train_data[i][w] = in_train_data[i][w];
    }
  }
  cout << "Input Data ready" << endl;
  return this;
}
Som *Som::get_bmu(double *input)
{
  this->bmu.dist = numeric_limits<double>::max();
  for (size_t row = 0; row < this->map_y; ++row)
  {
    for (size_t col = 0; col < this->map_x; ++col)
    {
      double tmp = get_distance(input, this->map[col][row]);
      if (tmp < this->bmu.dist)
      {
        this->bmu.dist = tmp;
        this->bmu.x = static_cast<unsigned long>(col);
        this->bmu.y = static_cast<unsigned long>(row);
      }
    }
  }
  this->bmu.dist = sqrt(this->bmu.dist);
  return this;
}
double Som::learning_linear(const size_t &iteration)
{
  return this->alpha * 1.0 / static_cast<double>(iteration);
}
Som *Som::init_alpha_values()
{
  this->alpha_values = static_cast<double *>(malloc(sizeof(double) * this->iteration_max));
  for (size_t iteration = 0; iteration < this->iteration_max; ++iteration)
    this->alpha_values[iteration] = learning_linear(iteration);
  cout << "Alpha values ready" << endl;
  return this;
}
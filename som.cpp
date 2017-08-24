#include "som_def.h"
#include <stdlib.h>
#include <iostream>
#include <random>

using namespace std;

Som::Som(unsigned long x, unsigned long y, unsigned long z) : alpha(7),
                                                              iteration_max(50),
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
double *Som::get_neighbor(const size_t &in_iteration)
{
  size_t x = this->bmu.x;
  size_t y = this->bmu.y;
  unsigned short radius = this->neighbor_radius[in_iteration];
  size_t x_start = x - radius;
  size_t x_end = x + radius;
  size_t y_start = y - radius;
  size_t y_end = y + radius;
  return this->map[0][0];
}

Som *Som::init_map()
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
        this->map[row][col][w] = dist(mt);
      }
    }
  }

  this->tmp = static_cast<double *>(malloc(sizeof(double) * this->map_z));
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

  delete[] this->tmp;
  cout << "Temp vector deleted" << endl;

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
  cout << "Input Data ready - " << this->train_data_size << " Datasets" << endl;
  return this;
}

Point Som::get_bmu(const double *input)
{
  this->bmu.dist = numeric_limits<double>::max();
  for (size_t row = 0; row < this->map_y; ++row)
  {
    for (size_t col = 0; col < this->map_x; ++col)
    {
      double tmp = get_distance(input, this->map[row][col], this->map_z);
      if (tmp < this->bmu.dist)
      {
        this->bmu.dist = tmp;
        this->bmu.x = static_cast<unsigned long>(col);
        this->bmu.y = static_cast<unsigned long>(row);
      }
    }
  }
  this->bmu.dist = sqrt(this->bmu.dist);
  return this->bmu;
}

double Som::get_distance(const double *v, const double *w, const size_t &n)
{
  auto result = .0;
  for (size_t i = 0; i < n; ++i)
    result += ((v[i] - w[i]) * (v[i] - w[i]));
  return result;
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
Som *Som::train_bmu(unsigned long iteration, double *input, double *weight)
{
  for (size_t w = 0; w < this->map_z; ++w)
  {
    weight[w] = weight[w] + alpha_values[iteration] * (input[w] - weight[w]);
  }
  return this;
}
vector<Point> Som::get_indices(const size_t &iteration, const Point &bmu)
{
  auto radius = this->neighbor_radius[iteration];
  size_t x = bmu.x;
  size_t y = bmu.y;
  vector<Point> idx;
  idx.resize(radius * 4 + radius * radius * 4);
  for(size_t i = 1; i <= radius; ++i){
    Point tmp;
    tmp.x 
  }
  // = r * 4 + r^2 * 4
  // 1 = 8
  // 2 = 24
  // 3 = 48
  // 4 = 80
}
Som *Som::start_training()
{
  cout << "start_training called" << endl;
  cout << this->train_data_size << endl;
  cout << this->iteration_max << endl;
  cout << this->map_z << endl;
  try
  {
    for (size_t c_iteration = 0; c_iteration < this->iteration_max; ++c_iteration)
    {
      cout << "IT: " << c_iteration << endl;
      for (size_t t = 0; t < this->train_data_size; ++t)
      // for (size_t t = 0; t <10; ++t)
      {
        Point bmu = get_bmu(this->train_data[t]);

        train(this->train_data[t], this->map[bmu.x][bmu.y], 0, c_iteration);
        train(this->train_data[t], this->map[bmu.x + 1][bmu.y], 1, c_iteration);
        train(this->train_data[t], this->map[bmu.x + 1][bmu.y + 1], 1, c_iteration);
        train(this->train_data[t], this->map[bmu.x][bmu.y + 1], 1, c_iteration);
      }
    }
  }
  catch (...)
  {
    cout << "Shit happens" << endl;
  }
  cout << this->bmu.x << endl;
  cout << this->bmu.y << endl;
  cout << this->bmu.dist << endl;
  return this;
}

double Som::lattice_width(const size_t &iteration)
{
  return this->neighbor_start * exp(-1 * (iteration / this->iteration_max));
}

double Som::neighbor_rate(const double &distance, const size_t &iteration)
{
  double o = lattice_width(iteration);
  o *= o;
  return exp(-((distance * distance) / (2 * o)));
}

// Es wird ein Neuron trainiert, dabei ist dinstance der Abstand zum BMU
Som *Som::train(const double *v, double *w, const unsigned short &distance, const size_t &iteration)
{
  for (size_t i = 0; i < this->map_z; ++i)
    tmp[i] = v[i] - w[i];
  double n_r = neighbor_rate(distance, iteration);
  for (size_t i = 0; i < this->map_z; ++i)
  {
    w[i] = w[i] + n_r * this->alpha_values[iteration] * tmp[i];
  }
  return this;
}

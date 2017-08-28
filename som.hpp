#pragma once
#include <math.h>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include "types.hpp"

using namespace std;
namespace b_velop
{
class Som
{
public:
  Som() : map_x(0), map_y(0), map_z(0), alpha(.7), iteration_max(2), neighbor_start(5) {}
  Som(size_t x, size_t y, size_t z);
  ~Som();
  Som *set_train_data(const vector<vector<double>> &in_train_data);
  Som *set_train_data(const Set *in_train_data);
  Som *set_alpha(const double &in_alpha);
  Som *set_iteration_max(const size_t &in_iteration_max);
  Som *set_neighbor_start(const size_t &in_neighbor_start);
  Som *set_dimensions(const size_t &rows, const size_t &columns);
  Som *start_training();
  Validation validation(const Set *set);
  static Som *open_map(const char *source);

  double learning_inverse_of_time(unsigned long iteration)
  {
    return this->alpha * (1.0 - static_cast<double>(iteration) / static_cast<double>(this->iteration_max));
  }
  double learing_power_series(unsigned long iteration)
  {
    return this->alpha * exp(static_cast<double>(iteration) / static_cast<double>(this->iteration_max));
  }
  // http://www.cis.hut.fi/somtoolbox/documentation/somalg.shtml
  // http://www.saedsayad.com/clustering_som.htm
  Som *init();

private:
  double ***map;
  bool map_rdy;
  size_t map_x;
  size_t map_y;
  size_t map_z;
  size_t iteration_max;
  size_t train_data_size;
  size_t neighbor_start;
  double alpha;
  double *alpha_values;
  double **train_data;
  size_t *neighbor_radius;
  vector<Point> b_velop::Som::get_indices(const size_t &iteration, const Point &bmu);

  Som *init_map();
  Som *init_alpha_values();
  Som *init_radius();
  Som *init_neighbor();
  Point get_bmu(const double *input);
  Som *save_map();
  // void get_bmu_mt(const double *input, const size_t &from, const size_t &to, Point &bmu);
  double lattice_width(const size_t &iteration);
  double neighbor_rate(const size_t &distance, const size_t &iteration);
  double get_distance(const double *v, const double *w, const size_t &n);
  Som *train_bmu(size_t iteration, double *input, double *weight);
  double learning_linear(const size_t &iteration);
  size_t get_neighbor_radius(const size_t &iteration);
  Som *train(const double *v, double *w, const size_t &distance, const size_t &iteration);
}; // Som
}

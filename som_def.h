#pragma once
#include <math.h>
#include <limits>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Merkmal
{
  string name;
  double max;
  double min;
};
void foo_bar(const char *source, vector<vector<double>> &out_scaled_data);
void parse_lines(const vector<string> &in_lines, vector<vector<double>> &out_values, vector<string> &header);
vector<Merkmal> get_merkmal(const vector<vector<double>> &in_values, const vector<string> &in_header);
struct Point
{
  unsigned long x;
  unsigned long y;
  double dist;
};
class Som
{
public:
  Som() : map_x(0), map_y(0), map_z(0), alpha(7), iteration_max(5000), neighbor_start(0) {}
  Som(unsigned long x, unsigned long y, unsigned long z);
  ~Som();

  Som *set_train_data(const vector<vector<double>> &in_train_data);
  Som *start_training();

  double learning_inverse_of_time(unsigned long iteration)
  {
    return this->alpha * (1.0 - static_cast<double>(iteration) / static_cast<double>(this->iteration_max));
  }
  double learing_power_series(unsigned long iteration)
  {
    return this->alpha * exp(static_cast<double>(iteration) / static_cast<double>(this->iteration_max));
  }

  double *get_bmu_vector()
  {
    return this->map[this->bmu.x][this->bmu.y];
  }
  // http://www.cis.hut.fi/somtoolbox/documentation/somalg.shtml
  // http://www.saedsayad.com/clustering_som.htm

  Som *init();

private:
  double ***map;
  bool map_rdy;
  size_t map_x;
  size_t map_y;
  unsigned long map_z;
  size_t iteration_max;
  size_t train_data_size;
  unsigned short neighbor_start;
  Point bmu;
  double alpha;
  double *alpha_values;
  double **train_data;
  unsigned short *neighbor_radius;

  Som *get_bmu(const double *input);
  Som *init_map();
  Som *init_alpha_values();
  Som *init_radius();
  double *get_neighbor(const size_t &in_iteration);
  double get_distance(const double *train_vector, double *weight);
  double learning_neighbor(const size_t &in_iteration, double *weight);
  Som *train_bmu(unsigned long iteration, double *input, double *weight);
  double learning_linear(const size_t &iteration);
  unsigned short get_neighbor_radius(const size_t &iteration);
}; // Som

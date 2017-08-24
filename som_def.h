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
  size_t x;
  size_t y;
  double dist;
};
class Som
{
public:
  Som() : map_x(0), map_y(0), map_z(0), alpha(.7), iteration_max(2), neighbor_start(5) {}
  Som(size_t x, size_t y, unsigned long z);
  ~Som();
  Som *set_train_data(const vector<vector<double>> &in_train_data);
  Som *start_training();
  static Som *open_map(const char *source);
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
  double *tmp;
  vector<Point> Som::get_indices(const size_t &iteration, const Point &bmu);

  Som *init_map();
  Som *init_alpha_values();
  Som *init_radius();
  Som *init_neighbor();
  Point get_bmu(const double *input);
  Som* save_map();
  // void get_bmu_mt(const double *input, const size_t &from, const size_t &to, Point &bmu);
  double lattice_width(const size_t &iteration);
  double neighbor_rate(const double &distance, const size_t &iteration);
  double get_distance(const double *v, const double *w, const size_t &n);
  Som *train_bmu(unsigned long iteration, double *input, double *weight);
  double learning_linear(const size_t &iteration);
  unsigned short get_neighbor_radius(const size_t &iteration);
  Som *train(const double *v, double *w, const unsigned short &distance, const size_t &iteration);
}; // Som

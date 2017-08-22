#include <math.h>
#include <limits>
using namespace std;

struct Point
{
  unsigned long x;
  unsigned long y;
  double dist;
};
struct parameter
{
  unsigned long map_x;
  unsigned long map_y;
  unsigned long map_z;
  unsigned long max_iterations; 
};
class Som
{
public:
<<<<<<< HEAD
  Som() : map_x(0), map_y(0), map_z(0), alpha(7), iteration_max(5000), neighbor_start(0) {}
  Som(unsigned long x, unsigned long y, unsigned long z);
=======
  Som() : map_x(0), map_y(0), map_z(0), map_rdy(false), max_itreations(0) {}
  Som(unsigned long x, unsigned long y, unsigned long z, unsigned long cnt);
>>>>>>> oo
  ~Som();
  Som *get_bmu(double *input)
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
  Som *set_train_data(const double **in_train_data, unsigned long size);
  double learning_linear(unsigned long iteration)
  {
    return this->alpha * 1.0 / static_cast<double>(iteration);
  }
  double learning_inverse_of_time(unsigned long iteration)
  {
    return this->alpha * (1.0 - static_cast<double>(iteration) / static_cast<double>(this->iteration_max));
  }
  double learing_power_series(unsigned long iteration)
  {
    return this->alpha * exp(static_cast<double>(iteration) / static_cast<double>(this->iteration_max));
  }

  // Gibt den derzeitigen Radius zurück (bezogen auf die Iteration)
  double neighbor_radius(unsigned long iteration)
  {
    return static_cast<unsigned short>(static_cast<double>(this->neighbor_start) * exp(-(static_cast<double>(iteration) / static_cast<double>(this->iteration_max))));
  }
  double *get_bmu_vector()
  {
    return this->map[this->bmu.x][this->bmu.y];
  }
  // http://www.cis.hut.fi/somtoolbox/documentation/somalg.shtml
  // http://www.saedsayad.com/clustering_som.htm
  double learning_neighbor(unsigned long iteration, double *weight)
  {
    // Nenner berechnen
    double tmp = 2.0 * (neighbor_radius(iteration) * neighbor_radius(iteration));
    double distance = sqrt(get_distance(this->get_bmu_vector(), weight));
    distance = distance * distance * -1.0;
    tmp = distance / tmp;
    tmp = learning_linear(iteration) * exp(tmp);
    return tmp;
  }
  double get_distance(double *train_vector, double *weight)
  {
    auto result = .0;
    for (size_t i = 0; i < this->map_z; ++i)
    {
      result += ((train_vector[i] - weight[i]) * (train_vector[i] - weight[i]));
    }
    return result;
  }
  Som *train_bmu(unsigned long iteration, double *input, double *weight)
  {
    for (size_t w = 0; w < this->map_z; ++w)
    {
      weight[w] = weight[w] + learning_linear(iteration) * (input[w] - weight[w]);
    }
    return this;
  }

private:
  double ***map;
  double **beta;
  double *alpha;
  bool map_rdy;
  unsigned long map_x;
  unsigned long map_y;
  unsigned long map_z;
<<<<<<< HEAD
  unsigned long iteration_max;
  unsigned long train_data_size;
  unsigned short neighbor_start;
  Point bmu;
  double alpha;
  double **train_data;

  Som *init();
=======
  unsigned long max_itreations;
  Som *init_map();
  Som *init_beta();
  Som *init_alpha();
>>>>>>> oo
}; // Som

struct map
{
  // y - x - z
  double ***weights;
};
void kill_memory(const parameter &para, map *som);
void init_networt(const parameter &parameter);

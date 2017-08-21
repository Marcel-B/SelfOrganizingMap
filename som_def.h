#include <math.h>

struct parameter
{
  unsigned long map_x;
  unsigned long map_y;
  unsigned long depth;
};
class Som
{
public:
  Som() : map_x(0), map_y(0), map_z(0), alpha(7), iteration_max(5000), neighbor_start(0) {}
  Som(unsigned long x, unsigned long y, unsigned long z);
  ~Som();
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
  double neighbor_radius(unsigned long iteration)
  {
    return static_cast<unsigned short>(static_cast<double>(this->neighbor_start) * exp(-(static_cast<double>(iteration) / static_cast<double>(this->iteration_max))));
  }
  // http://www.cis.hut.fi/somtoolbox/documentation/somalg.shtml
  // http://www.saedsayad.com/clustering_som.htm
  double learning_neighbor(unsigned long iteration)
  {
    double distance = 0.2; // <== distance = euklidische distanz zwischen training und ...
    double first = exp(-(distance * distance) / 2.0 * (neighbor_radius(iteration) * neighbor_radius(iteration));
    // (- abs( (current_winner - weight[x][y])*(current_winner - weight[x][y]) ) ) / ( 2 * (neighbor_radius(iteration)) )
    learning_linear(iteration) * exp(1 / (2.0 * (neighbor_radius(iteration) * neighbor_radius(iteration))));
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
  /// Learing function:
  // w(t+1) = w(t) + a(t)
  double w(double current_weight, unsigned long iteration)
  {
    double gewicht;                                     // Aktuelles gewicht
    return current_weight + learning_linear(iteration); // * h(iteration) * (eingang(it) - gewicht);
  }

  double train(unsigned long iteration)
  {
    // neuron_neu = neuron + lernen(iteration) * nachbar(iteration) * (input - neuron);
  }

private:
  double ***map;
  unsigned long map_x;
  unsigned long map_y;
  unsigned long map_z;
  unsigned long iteration_max;
  unsigned short neighbor_start;
  double alpha;
  Som *init();
}; // Som

struct map
{
  // y - x - z
  double ***weights;
};
void kill_memory(const parameter &para, map *som);
void init_networt(const parameter &parameter);

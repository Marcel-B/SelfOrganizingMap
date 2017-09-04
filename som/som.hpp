#pragma once
#include <math.h>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include "../infrastructure/types.hpp"
#include "../infrastructure/set.h"
#include <cstddef>


using namespace std;
namespace com_b_velop
{
  class Som
  {
  public:
    Som() : map_x(0), map_y(0), map_z(0), alpha(.7), iteration_max(2), neighbor_start(5) {}
    Som(size_t x, size_t y, size_t z);
    ~Som();
    Som *SetTrainData(const vector<vector<double>> &in_train_data);
    Som *set_train_data(const com_b_velop::Set *in_train_data);
    Som *SetAlpha(const double &in_alpha);
    Som *set_iteration_max(const size_t &in_iteration_max);
    Som *set_neighbor_start(const size_t &in_neighbor_start);
    Som *SetDimension(const size_t &rows, const size_t &columns);
    Som *StartTraining();
    Validation Validation(const Set *set);
    static Som *OpenMap(const char *source);

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
    vector<Point> get_indices(const size_t &iteration, const Point &bmu);

    /**
     * Die Speicher für die Karte wird allokiert. Alle Gewichte werden mit zufälligen Werten
     * zwischen 0.0 und 1.0 vorbelegt.
     * @return das aufrufende Som-Objekt
     */
    Som *InitMap();

    /**
     * Es wird ein Feld mit den jeweiligen, iterationsabhängigen Lernraten erstellt.
     * @return das aufrufende Som-Objekt
     */
    Som *InitAlphaValues();

    /**
     * Es wird ein Feld mit den jeweiligen, iterationsabhängigen Nachbarradien erstellt.
     * @return das aufrufende Som-Objekt
     */
    Som *InitRadius();


    Som *init_neighbor();

    /**
     * Bmu Suche. Die Funktion durchläuft die gesamte und sucht das Neuron, was input am ähnlichsten ist.
     * Die Koordinate und die Distanz werden in Point festgehalten.
     * @param input Ein Vektor der eine Zeile aus den Trainingsdaten enthält
     * @return Ein Point-Objekt mit den Koordinaten des BMU und der Distanz zum BMU
     */
    Point GetBmu(const double *input);
    Som *save_map();
    // void get_bmu_mt(const double *input, const size_t &from, const size_t &to, Point &bmu);
    double lattice_width(const size_t &iteration);
    double NeighborRate(const size_t &distance, const size_t &iteration);
    double get_distance(const double *v, const double *w, const size_t &n);
    Som *TrainBmu(size_t iteration, double *input, double *weight);
    double learning_linear(const size_t &iteration);
    size_t get_neighbor_radius(const size_t &iteration);
    Som *Train(const double *v, double *w, const size_t &distance, const size_t &iteration);
  }; // Som
} // namespace com_b_velop

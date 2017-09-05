#include "som.hpp"
#include "../SelfOrganizinMap.Infrastructure/types.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm> // std::random_shuffle
#include <thread>
#include <stdlib.h>
#include "../SelfOrganizinMap.Infrastructure/help.h"
#include "../SelfOrganizinMap.Infrastructure/set.h"

using namespace std;
namespace com_b_velop
{
  Som::Som(size_t x, size_t y, size_t z) : alpha(.7),
                                           iteration_max(2),
                                           neighbor_start(5)
  {
    this->map_x = x;
    this->map_y = y;
    this->map_z = z;
    size_t bigger = x < y ? x : y;
    bigger = bigger / 2 - 1;
    this->neighbor_start = this->neighbor_start > bigger ? bigger : this->neighbor_start;
    cout << "Initialization ready" << endl;
  }
  size_t Som::get_neighbor_radius(const size_t &iteration)
  {
    return static_cast<size_t>(static_cast<double>(this->neighbor_start)
                               * exp(-(static_cast<double>(iteration)
                                       / static_cast<double>(this->iteration_max))));
  }
  Som *Som::InitRadius()
  {
    this->neighbor_radius = static_cast<size_t *>(malloc(sizeof(size_t) * this->iteration_max));
    for (size_t iteration = 0; iteration < this->iteration_max; ++iteration)
      this->neighbor_radius[iteration] = get_neighbor_radius(iteration);
    cout << "Neighbor radius ready" << endl;
    return this;
  }
  Som *Som::InitMap()
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
    cout << "Map ready" << endl;
    return this;
  }
  Som *Som::SetAlpha(const double &in_alpha)
  {
    this->alpha = in_alpha;
    return this;
  }
  Som *Som::set_iteration_max(const size_t &in_iteration_max)
  {
    this->iteration_max = in_iteration_max;
    return this;
  }
  Som *Som::set_neighbor_start(const size_t &in_neighbor_start)
  {
    size_t bigger = this->map_x < this->map_y ? this->map_x : this->map_y;
    bigger = bigger / 2 - 1;
    this->neighbor_start = in_neighbor_start > bigger ? bigger : in_neighbor_start;
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
  Som *Som::set_train_data(const Set *in_train_data)
  {
    this->train_data_size = in_train_data->rows;
    this->train_data = static_cast<double **>(malloc(sizeof(double *) * this->train_data_size));
    for (size_t i = 0; i < this->train_data_size; ++i)
    {
      this->train_data[i] = static_cast<double *>(malloc(sizeof(double) * in_train_data->cols));
      for (size_t w = 0; w < in_train_data->cols; ++w)
      {
        this->train_data[i][w] = in_train_data->values[i][w];
      }
    }
    cout << "Input Data ready - " << this->train_data_size << " Datasets" << endl;
    return this;
  }

// Die Traingsdaten kopieren
  Som *Som::SetTrainData(const vector<vector<double>> &in_train_data)
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

  Point Som::GetBmu(const double *input)
  {
    Point bmu;
    bmu.dist = numeric_limits<double>::max();

    for (size_t row = 0; row < this->map_y; ++row)
    {
      for (size_t col = 0; col < this->map_x; ++col)
      {
        double tmp = get_distance(input, this->map[row][col], this->map_z);
        if (tmp < bmu.dist)
        {
          bmu.dist = tmp;
          bmu.x = static_cast<unsigned long>(col);
          bmu.y = static_cast<unsigned long>(row);
        }
      }
    }
    bmu.dist = sqrt(bmu.dist);
    return bmu;
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
    return this->alpha * 1.0 / static_cast<double>((iteration + 1));
  }

  Som *Som::InitAlphaValues(){
    this->alpha_values = static_cast<double *>(malloc(sizeof(double) * this->iteration_max));
    this->alpha_values[0] = this->alpha;
    for (size_t iteration = 1; iteration < this->iteration_max; ++iteration)
    {
      this->alpha_values[iteration] = learning_linear(iteration);
    }
    cout << "Alpha values ready" << endl;
    return this;
  }
  Som *Som::TrainBmu(size_t iteration, double *input, double *weight){
    for (size_t w = 0; w < this->map_z; ++w)
    {
      weight[w] = weight[w] + alpha_values[iteration] * (input[w] - weight[w]);
    }
    return this;
  }
  vector<Point> Som::get_indices(const size_t &iteration, const Point &bmu){
    long long radius = static_cast<long long>(this->neighbor_radius[iteration]);
    long long x = bmu.x;
    long long y = bmu.y;
    long long tmp_x;
    long long tmp_y;
    size_t width = this->map_x;
    size_t height = this->map_y;
    vector<Point> idx;
    for (long long r_x = -radius; r_x <= radius; ++r_x)
    {
      tmp_x = x - r_x;
      tmp_x = tmp_x < 0 ? width + tmp_x : tmp_x;
      tmp_x = tmp_x >= width ? tmp_x - width : tmp_x;
      for (long long r_y = -radius; r_y <= radius; ++r_y)
      {
        Point tmp;
        tmp_y = y - r_y;
        tmp_y = tmp_y < 0 ? height + tmp_y : tmp_y;
        tmp_y = tmp_y >= height ? tmp_y - height : tmp_y;
        tmp.y = tmp_y;
        tmp.x = tmp_x;
        tmp.dist = abs(r_x) >= abs(r_y) ? static_cast<double>(abs(r_x)) : static_cast<double>(abs(r_y));
        idx.push_back(tmp);
      }
    }
    return idx;
  }
  void get_bmu_mt(const double *input,
                  const size_t &from,
                  const size_t &to,
                  double ***map,
                  size_t n,
                  size_t w,
                  Point *bmu){
    bmu->dist = numeric_limits<double>::max();

    for (size_t row = from; row < to; ++row)
    {
      for (size_t col = 0; col < w; ++col)
      {
        double tmp = 0;
        for (size_t i = 0; i < n; ++i)
          tmp += ((input[i] - map[row][col][i]) * (input[i] - map[row][col][i]));
        if (tmp < bmu->dist)
        {
          bmu->dist = tmp;
          bmu->x = (col);
          bmu->y = (row);
        }
      }
    }
    bmu->dist = sqrt(bmu->dist);
  }
  Som *Som::SetDimension(const size_t &rows, const size_t &columns){
    this->map_x = columns;
    this->map_y = rows;
    size_t bigger = this->map_x < this->map_y ? this->map_x : this->map_y;
    bigger = bigger / 2 - 1;
    this->neighbor_start = this->neighbor_start > bigger ? bigger : this->neighbor_start;
    return this;
  }

  /**
   * Die Iteration wird in gang gesetzt. Die Karte
   * wird nach Vorgabe trainiert und anschließend gespeichert.
   * @return Die trainierte Karte
   */
  Som *Som::StartTraining(){
    cout << "StartTraining called" << endl;
    InitMap()->InitAlphaValues()->InitRadius();
    cout << this->train_data_size << endl;
    cout << this->iteration_max << endl;
    cout << this->map_z << endl;
    vector<double> dist;
    double distance = 0;
    vector<size_t> indices;
    auto bmu1 = new Point();
    auto bmu2 = new Point();
    Point bmu;
    for (size_t i = 0; i < this->train_data_size; ++i)
    {
      indices.push_back(i);
    }
    try
    {
      for (size_t c_iteration = 0; c_iteration < this->iteration_max; ++c_iteration)
      {
        std::random_shuffle(indices.begin(), indices.end());
        distance = 0;
        cout << "|=================================|" << endl;
        cout << left << setw(22) << setfill('_') <<  "|Iteration" << setw(12) << right << (c_iteration + 1) <<"|"<< endl;

        for (size_t t = 0; t < this->train_data_size; ++t)
        {
          auto td = this->train_data[indices[t]];
          //Point bmu = get_bmu(this->train_data[indices[t]]);
          thread th1(get_bmu_mt, td, 0, this->map_y / 2, this->map, this->map_z, this->map_x, bmu1);
          thread th2(get_bmu_mt, td, this->map_y / 2 + 1, this->map_y, this->map, this->map_z, this->map_x, bmu2);
          th1.join();
          th2.join();
          if (bmu1->dist < bmu2->dist)
          {
            bmu.dist = bmu1->dist;
            bmu.x = bmu1->x;
            bmu.y = bmu1->y;
          }
          else
          {
            bmu.dist = bmu2->dist;
            bmu.x = bmu2->x;
            bmu.y = bmu2->y;
          }
          distance += bmu.dist;
          auto idx = get_indices(c_iteration, bmu);
          for (size_t i = 0; i < idx.size(); ++i)
            Train(this->train_data[indices[t]], this->map[idx[i].y][idx[i].x], static_cast<size_t>(idx[i].dist),
                  c_iteration);
        }

        cout << left << setw(22) << "|Quantiziation Error" << setw(12) << right << setprecision(8) << (distance / this->train_data_size) <<"|"<< endl;
        cout << left << setw(22) << "|Alpha" << setw(12) << right  << setprecision(8) << this->alpha_values[c_iteration]<<"|" << endl;
        cout << left << setw(22) << "|Radius" << setw(12) << right << setprecision(8)  << this->neighbor_radius[c_iteration] <<"|"<< endl;
        dist.push_back(distance / this->train_data_size);
      }
    } // c_iteration
    catch (...)
    {
      cout << "Shit happens" << endl;
    }
    auto dd = .0;
    auto mintr = 50.0;
    for (size_t i = 0; i < dist.size(); ++i)
    {
      dd += dist[i];
      mintr = mintr < dist[i] ? mintr : dist[i];
    }
    dd /= dist.size();
    cout << "|=================================|" << endl;

    cout << setw(22) << left
         << "|Train Distance Avg" << setw(12) << right << setprecision(8) <<  dd<<"|" << endl;
    cout << setw(22) << left
         << "|Train Distance Min" << setw(12) << right << setprecision(8) <<  mintr <<"|"<< endl;
    cout << setw(22) << left
         << "|Train Distance Last" << setw(12) << right << setprecision(8) <<  dist[dist.size()-1]<<"|" << endl;
    delete bmu1;
    delete bmu2;
    SaveMap();
    return this;
  }
  Som *Som::OpenMap(const char *source){
    auto som = new Som();
    ifstream myFile;
    myFile.open(source, ios::in | ios::binary);
    myFile.read((char *)&som->map_x, sizeof(som->map_x));
    myFile.read((char *)&som->map_y, sizeof(som->map_y));
    myFile.read((char *)&som->map_z, sizeof(som->map_z));
    myFile.read((char *)&som->iteration_max, sizeof(som->iteration_max));
    myFile.read((char *)&som->train_data_size, sizeof(som->train_data_size));
    myFile.read((char *)&som->neighbor_start, sizeof(som->neighbor_start));
    myFile.read((char *)&som->alpha, sizeof(som->alpha));
    som->InitMap()->InitMap()->InitMap();
    for (size_t row = 0; row < som->map_y; ++row)
      for (size_t col = 0; col < som->map_x; ++col)
        for (size_t w = 0; w < som->map_z; ++w)
        {
          myFile.read((char *)&som->map[row][col][w], sizeof(som->map[row][col][w]));
          cout << som->map[row][col][w] << endl;
        }
    myFile.close();
    return som;
  }
  double Som::lattice_width(const size_t &iteration){
    return this->neighbor_start * exp(-1 * (iteration / this->iteration_max));
  }
  Som *Som::SaveMap(){
    ofstream myFile;
    myFile.open("som.som", ios::out | ios::binary);
    myFile.write((char *)&this->map_x, sizeof(this->map_x));
    myFile.write((char *)&this->map_y, sizeof(this->map_y));
    myFile.write((char *)&this->map_z, sizeof(this->map_z));
    myFile.write((char *)&this->iteration_max, sizeof(this->iteration_max));
    myFile.write((char *)&this->train_data_size, sizeof(this->train_data_size));
    myFile.write((char *)&this->neighbor_start, sizeof(this->neighbor_start));
    myFile.write((char *)&this->alpha, sizeof(this->alpha));

    for (size_t row = 0; row < this->map_y; ++row)
      for (size_t col = 0; col < this->map_x; ++col)
        for (size_t w = 0; w < this->map_z; ++w)
        {
          myFile.write((char *)&this->map[row][col][w], sizeof(this->map[row][col][w]));
        }
    myFile.close();
    return this;
  }
  double Som::NeighborRate(const size_t &distance, const size_t &iteration){
    double o = lattice_width(iteration);
    o *= o;
    return exp(-((distance * distance) / (2 * o)));
  }

// Es wird ein Neuron trainiert, dabei ist dinstance der Abstand zum BMU
  Som *Som::Train(const double *v, double *w, const size_t &distance, const size_t &iteration){
    double n_r = NeighborRate(distance, iteration);
    for (size_t i = 0; i < this->map_z; ++i)
      w[i] = w[i] + n_r * this->alpha_values[iteration] * (v[i] - w[i]);
    return this;
  }
  com_b_velop::Validation Som::Validation(const Set *set){
    com_b_velop::Validation validation;
    double v = 0;
    vector<com_b_velop::ValidSet> vs;
    for (size_t row = 0; row < set->rows; ++row)
    {
      auto bmu = GetBmu(set->values[row]);
      ValidSet tmp;
      tmp.w = this->map_z;
      for (size_t w = 0; w < tmp.w; ++w)
      {
        auto j = set->values[row][w];
        auto u = this->map[bmu.y][bmu.x][w];
        tmp.delta.push_back(j - u);
        j = com_b_velop::Help::ScaleValue(j, 0, 1, set->features[w].min, set->features[w].max);
        tmp.in.push_back(j);
        // tmp.in.push_back(set->values[row][w]);
        u = com_b_velop::Help::ScaleValue(u, 0, 1, set->features[w].min, set->features[w].max);
        // tmp.out.push_back(this->map[bmu.y][bmu.x][w]);
        tmp.out.push_back(u);
        tmp.x = bmu.x;
        tmp.y = bmu.y;
        tmp.d = bmu.dist;
      }
      vs.push_back(tmp);
      v += bmu.dist;
    }
    v /= vs.size();
    validation.valid_set = vs;
    validation.distance = v;
    cout << "|=================================|" << endl;
    cout << left << setw(22) << "|Validation Distance" << setprecision(8) << right << setw(12) << v <<"|"<< endl;
    cout << setw(22) << left << "|Test Data Size" << setw(12) << right << setprecision(8)  << validation.valid_set.size()<<"|" << endl;
    cout << "|=================================|" << endl;

    return validation;
  }
}
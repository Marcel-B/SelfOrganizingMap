#include "som_def.h"
#include <stdlib.h>
#include <random>
#include <iostream>

using namespace std;

void init_networt(const parameter &parameter)
{
  unsigned long rows = parameter.map_y;
  unsigned long cols = parameter.map_x;
  unsigned long weights = parameter.depth;
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  map *som = (map *)malloc(sizeof(map));
  som->weights = (double ***)malloc(sizeof(double **) * rows);
  for (size_t row = 0; row < rows; ++row)
  {
    som->weights[row] = (double **)malloc(sizeof(double *) * cols);
    for (size_t col = 0; col < cols; ++col)
    {
      som->weights[row][col] = (double *)malloc(sizeof(double) * weights);
      for (size_t w = 0; w < weights; ++w)
      {
        som->weights[row][col][w] = dist(mt);
        cout << som->weights[row][col][w] << endl;
      }
    }
  }
  kill_memory(parameter, som);
}

void kill_memory(const parameter &para, map *som)
{
  unsigned long rows = para.map_y;
  unsigned long cols = para.map_x;
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  for (size_t row = 0; row < rows; ++row)
  {
    for (size_t col = 0; col < cols; ++col)
    {
      delete[] som->weights[row][col];
    }
    delete[] som->weights[row];
  }
  delete[] som->weights;
  delete som;

  cout << "Ende" << endl;
}
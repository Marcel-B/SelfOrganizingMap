#include "som_def.h"
#include <stdlib>
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
  map->weights = (double ***)malloc(sizeof(double **) * rows);
  for (size_t row = 0; row < rows; ++row)
  {
    som[row] = (double **)malloc(sizeof(double *) * cols);
    for (size_t col = 0; col < cols; ++col)
    {
      som[row][col] = (double *)malloc(sizeof(double) * weights);
      for(size_t w = 0; w < weights; ++w)
      som[row][col][w] =  dist(mt);
      cout << som[row][col][w] << endl;
    }
  }
  for(size_t row = 0; row < rows; ++row)
  {
    for(size_t col = 0; col < cols; ++col){
      delete [] som[row][col];
    }
    delete [] som[row]
  }
  delete [] som;
  cout << "Ende" << endl;
}
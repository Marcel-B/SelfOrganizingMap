#pragma once
#include <vector>
#include "som.hpp"
#include "types.hpp"

namespace b_velop
{
struct In_Out
{
  static double scale_value(double x, double min, double max, double a, double b);
  static vector<double> scale_values(const vector<double> &in_column_vector);
  static void import_data(const char *source, vector<vector<double>> &out_scaled_data);
  static void parse_lines(const vector<string> &in_lines, vector<vector<double>> &out_values, vector<string> &header);
  static vector<Merkmal> get_merkmal(const vector<vector<double>> &in_values, const vector<string> &in_header);
  static void save_set(const Set *in_set, const char *destination);
};
}

#pragma once
#include <vector>
#include "../som/som.hpp"
#include "feature.h"
#include "types.hpp"
#include "set.h"

namespace com_b_velop
{
  struct InOut
  {
    static vector<double> ScaleValues(const vector<double> &in_column_vector);
    static void ImportData(const char *source, com_b_velop::Set *out_scaled_data);
    static void ParseLines(const vector<string> &in_lines, vector<vector<double>> &out_values, vector<string> &header);
    static vector<Feature> GetFeatures(const vector<vector<double>> &in_values, const vector<string> &in_header);
    static void SaveSet(const Set *in_set, const char *destination);
  };
} // namespace com_b_velop

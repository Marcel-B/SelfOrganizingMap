#pragma once
#include <vector>
#include "feature.h"
#include "set.h"

namespace com_b_velop
{
  struct InOut
  {
    static std::vector<double> scale_values(const std::vector<double> &in_column_vector);
    static void import_data(const char *source, com_b_velop::Set *out_scaled_data);
    static void parse_lines(const std::vector<std::string> &in_lines, std::vector<std::vector<double>> &out_values, std::vector<std::string> &header);
    static std::vector<Feature> get_features(const std::vector<std::vector<double>> &in_values, const std::vector<std::string> &in_header);
    static void save_set(const Set *in_set, const char *destination);
  };
} // namespace com_b_velop

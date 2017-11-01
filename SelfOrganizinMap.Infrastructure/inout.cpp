#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include "inout.h"
#include "types.hpp"
#include <algorithm>
#include "help.h"
#include "set.h"

#define SEP ','

namespace com_b_velop
{
	std::vector<double> InOut::scale_values(const std::vector<double> &in_column_vector)
  {
	  std::vector<double> scaled;
    scaled.resize(in_column_vector.size());
    double max = std::numeric_limits<double>::lowest();
    double min = std::numeric_limits<double>::max();
    double range;
    for (size_t i = 0; i < in_column_vector.size(); ++i)
    {
      max = max < in_column_vector[i] ? in_column_vector[i] : max;
      min = min > in_column_vector[i] ? in_column_vector[i] : min;
    }
    range = max - min;
    if (range > 0)
      for (size_t i = 0; i < in_column_vector.size(); ++i)
        scaled[i] = Help::ScaleValue(in_column_vector[i], min, max, 0.01, 0.99);
    else // Konstante
      for (size_t i = 0; i < in_column_vector.size(); ++i)
        scaled[i] = 0.05;
    return scaled;
  }
  void InOut::save_set(const com_b_velop::Set *in_set, const char *destination)
  {
	  std::ofstream of;
    of.open(destination, std::ios::out);
    if (of.is_open())
    {
      for (size_t row = 0; row < in_set->rows; ++row)
      {
        of << in_set->values[row][0];
        for (size_t col = 1; col < in_set->cols; ++col)
          of << SEP << in_set->values[row][col];
        of << std::endl;
      }
      of.close();
    }
  }

/**
 * Data will be imported
 * @param source Path to the formated csv-File
 * @param out_scaled_data 2D vector<double> with scaled data between 0 and 1
 */
	void InOut::import_data(const char *source, com_b_velop::Set *out_set)
	{
		std::string line;
		std::ifstream fs;
		std::vector<std::string> lines;
		std::cout << "Path: " << source << std::endl;
		fs.open(source, std::ios::in);
		if (fs.is_open())
			while (getline(fs, line))
				lines.push_back(line);
		else
		{
			std::cout << "Quelle nicht vorhanden" << std::endl;
			exit(1);
			fs.close();
		}
			//throw "Source doesn't exist";
    fs.close();

		std::vector<std::vector<double>> values;
		std::vector<std::string> header;

    parse_lines(lines, values, header);
    auto features = get_features(values, header);
    out_set->features = features;
    out_set->features_size = features.size();
    size_t hlen = 0;
    for (size_t i = 0; i < header.size(); ++i)
      hlen = hlen < header[i].size() ? header[i].size() : hlen;
    hlen += 3;
		std::cout << std::setw(hlen) << std::left << "Name" << std::right << std::setw(12) << "min" << std::setw(12) << "max" << std::endl;
    for (size_t i = 0; i < features.size(); ++i)
	    std::cout << features[i].ToString(hlen) << std::endl;

		std::vector<double> tmp_col;
    for (size_t i = 0; i < header.size(); ++i)
    {
      tmp_col.clear();
      for (size_t row = 0; row < values.size(); ++row)
      {
        tmp_col.push_back(values[row][i]);
      }
      // Spalte skalieren
      auto column = scale_values(tmp_col);

      // Skalierten Werte zurückschreiben
      for (size_t row = 0; row < values.size(); ++row)
      {
        values[row][i] = column[row];
      }
    }
    out_set->SetSet(values);
  }

	std::vector<Feature> InOut::get_features(const std::vector<std::vector<double>> &in_values, const std::vector<std::string> &in_header)
  {
	  std::vector<Feature> ret_value;
    for (size_t col = 0; col < in_header.size(); ++col)
    {
      Feature tmp;
      tmp.min = std::numeric_limits<double>::max();
      tmp.max = std::numeric_limits<double>::lowest();
      tmp.name = in_header[col];
      for (size_t row = 0; row < in_values.size(); ++row)
      {
        tmp.min = in_values[row][col] < tmp.min ? in_values[row][col] : tmp.min;
        tmp.max = in_values[row][col] > tmp.max ? in_values[row][col] : tmp.max;
      }
      ret_value.push_back(tmp);
    }
    return ret_value;
  }
  void InOut::parse_lines(const std::vector<std::string> &in_lines, std::vector<std::vector<double>> &out_values, std::vector<std::string> &out_header)
  {
	  std::string header_row = in_lines[0];
	  std::string current_row;
	  std::string tmp;
    int idx = 0;
    do
    {
      idx = static_cast<int>(header_row.find(SEP));
      if (idx < 0)
      {
        out_header.push_back(header_row);
      }
      else
      {
        out_header.push_back(header_row.substr(0, idx));
        header_row = header_row.substr(idx + 1);
      }
    } while (idx >= 0);

    for (size_t i = 1; i < in_lines.size(); ++i)
    {
	    std::vector<double> row;
      current_row = in_lines[i];
      do
      {
        idx = static_cast<int>(current_row.find(SEP));
        if (idx < 0)
        {
          row.push_back(stod(current_row));
        }
        else
        {
          row.push_back(stod(current_row.substr(0, idx)));
          current_row = current_row.substr(idx + 1);
        }
      } while (idx >= 0);
      out_values.push_back(row);
    }
  }
} // namespace com_b_velop

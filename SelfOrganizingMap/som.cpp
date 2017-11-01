#include "som.hpp"
#include "../SelfOrganizinMap.Infrastructure/types.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm> // std::random_shuffle
#include <thread>
#include "../SelfOrganizinMap.Infrastructure/help.h"
#include "../SelfOrganizinMap.Infrastructure/set.h"

namespace com_b_velop
{
	Som::Som(size_t x, size_t y, size_t z) :
		map_(nullptr),
		map_rdy_(false),
		map_x_(x),
		map_y_(y),
		map_z_(z),
		iteration_max_(2),
		train_data_size_(0),
		neighbor_start_(5),
		alpha_(.7),
		alpha_values_(nullptr),
		train_data_(nullptr),
		neighbor_radius_(nullptr)
	{
		auto bigger = x < y ? x : y;
		bigger = bigger / 2 - 1;
		this->neighbor_start_ = this->neighbor_start_ > bigger ? bigger : this->neighbor_start_;
		std::cout << "Initialization ready" << std::endl;
	}

	size_t Som::GetNeighborRadius(const size_t &iteration) const
	{
		return static_cast<size_t>(static_cast<double>(this->neighbor_start_)
			* exp(-(static_cast<double>(iteration)
				/ static_cast<double>(this->iteration_max_))));
	}
	Som *Som::InitRadius()
	{
		this->neighbor_radius_ = static_cast<size_t *>(malloc(sizeof(size_t) * this->iteration_max_));
		for (size_t iteration = 0; iteration < this->iteration_max_; ++iteration)
			this->neighbor_radius_[iteration] = GetNeighborRadius(iteration);
		std::cout << "Neighbor radius ready" << std::endl;
		return this;
	}
	Som *Som::InitMap()
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(0.0, 1.0);
		this->map_ = static_cast<double ***>(malloc(sizeof(double **) * this->map_y_));
		for (size_t row = 0; row < this->map_y_; ++row)
		{
			this->map_[row] = static_cast<double **>(malloc(sizeof(double *) * this->map_x_));
			for (size_t col = 0; col < this->map_x_; ++col)
			{
				this->map_[row][col] = static_cast<double *>(malloc(sizeof(double) * this->map_z_));
				for (size_t w = 0; w < this->map_z_; ++w)
				{
					this->map_[row][col][w] = dist(mt);
				}
			}
		}
		std::cout << "Map ready" << std::endl;
		return this;
	}
	Som *Som::SetAlpha(const double &in_alpha)
	{
		this->alpha_ = in_alpha;
		return this;
	}
	Som *Som::SetIterationMax(const size_t &in_iteration_max)
	{
		this->iteration_max_ = in_iteration_max;
		return this;
	}
	Som *Som::SetNeighborStart(const size_t &in_neighbor_start)
	{
		size_t bigger = this->map_x_ < this->map_y_ ? this->map_x_ : this->map_y_;
		bigger = bigger / 2 - 1;
		this->neighbor_start_ = in_neighbor_start > bigger ? bigger : in_neighbor_start;
		return this;
	}
	Som::~Som()
	{
		std::cout << "Som deallocate process started" << std::endl;
		for (size_t row = 0; row < this->map_y_; ++row)
		{
			for (size_t col = 0; col < this->map_x_; ++col)
			{
				delete[] this->map_[row][col];
			}
			delete[] this->map_[row];
		}
		delete[] this->map_;
		std::cout << "Map deleted" << std::endl;
		for (size_t i = 0; i < this->train_data_size_; ++i)
		{
			delete[] this->train_data_[i];
		}
		delete[] this->train_data_;
		std::cout << "Train values deleted" << std::endl;

		delete[] this->alpha_values_;
		std::cout << "Alpha values deleted" << std::endl;

		delete[] this->neighbor_radius_;
		std::cout << "Neighbor radius deleted" << std::endl;

		std::cout << "Som deallocate process finished (" << this << ")" << std::endl;
	}
	Som *Som::SetTrainData(const Set *in_train_data)
	{
		this->train_data_size_ = in_train_data->rows;
		this->train_data_ = static_cast<double **>(malloc(sizeof(double *) * this->train_data_size_));
		for (size_t i = 0; i < this->train_data_size_; ++i)
		{
			this->train_data_[i] = static_cast<double *>(malloc(sizeof(double) * in_train_data->cols));
			for (size_t w = 0; w < in_train_data->cols; ++w)
			{
				this->train_data_[i][w] = in_train_data->values[i][w];
			}
		}
		std::cout << "Input Data ready - " << this->train_data_size_ << " Datasets" << std::endl;
		return this;
	}

	// Die Traingsdaten kopieren
	Som *Som::SetTrainData(const std::vector<std::vector<double>> &in_train_data)
	{
		this->train_data_size_ = in_train_data.size();
		this->train_data_ = static_cast<double **>(malloc(sizeof(double *) * this->train_data_size_));
		for (size_t i = 0; i < this->train_data_size_; ++i)
		{
			this->train_data_[i] = static_cast<double *>(malloc(sizeof(double) * in_train_data[i].size()));
			for (size_t w = 0; w < in_train_data[i].size(); ++w)
			{
				this->train_data_[i][w] = in_train_data[i][w];
			}
		}
		std::cout << "Input Data ready - " << this->train_data_size_ << " Datasets" << std::endl;
		return this;
	}

	Point Som::GetBmu(const double *input)
	{
		Point bmu;
		bmu.dist = std::numeric_limits<double>::max();

		for (size_t row = 0; row < this->map_y_; ++row)
		{
			for (size_t col = 0; col < this->map_x_; ++col)
			{
				const auto tmp = GetDistance(input, this->map_[row][col], this->map_z_);
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

	double Som::GetDistance(const double *v, const double *w, const size_t &n) const
	{
		auto result = .0;
		for (size_t i = 0; i < n; ++i)
			result += ((v[i] - w[i]) * (v[i] - w[i]));
		return result;
	}
	double Som::LearningLinear(const size_t &iteration) const
	{
		return this->alpha_ * 1.0 / static_cast<double>((iteration + 1));
	}

	Som *Som::InitAlphaValues() {
		this->alpha_values_ = static_cast<double *>(malloc(sizeof(double) * this->iteration_max_));
		this->alpha_values_[0] = this->alpha_;
		for (size_t iteration = 1; iteration < this->iteration_max_; ++iteration)
		{
			this->alpha_values_[iteration] = LearningLinear(iteration);
		}
		std::cout << "Alpha values ready" << std::endl;
		return this;
	}
	Som *Som::TrainBmu(size_t iteration, double *input, double *weight) {
		for (size_t w = 0; w < this->map_z_; ++w)
		{
			weight[w] = weight[w] + alpha_values_[iteration] * (input[w] - weight[w]);
		}
		return this;
	}

	std::vector<Point> Som::GetIndices(const size_t &iteration, const Point &bmu) const
	{
		long long radius = static_cast<long long>(this->neighbor_radius_[iteration]);
		long long x = bmu.x;
		long long y = bmu.y;
		long long tmp_x;
		long long tmp_y;
		size_t width = this->map_x_;
		size_t height = this->map_y_;
		std::vector<Point> idx;
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
		Point *bmu) {
		bmu->dist = std::numeric_limits<double>::max();

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
	Som *Som::SetDimension(const size_t &rows, const size_t &columns) {
		this->map_x_ = columns;
		this->map_y_ = rows;
		size_t bigger = this->map_x_ < this->map_y_ ? this->map_x_ : this->map_y_;
		bigger = bigger / 2 - 1;
		this->neighbor_start_ = this->neighbor_start_ > bigger ? bigger : this->neighbor_start_;
		return this;
	}

	/**
	 * Die Iteration wird in gang gesetzt. Die Karte
	 * wird nach Vorgabe trainiert und anschließend gespeichert.
	 * @return Die trainierte Karte
	 */
	Som *Som::StartTraining() {
		std::cout << "StartTraining called" << std::endl;
		InitMap()->InitAlphaValues()->InitRadius();
		std::cout << this->train_data_size_ << std::endl;
		std::cout << this->iteration_max_ << std::endl;
		std::cout << this->map_z_ << std::endl;
		std::vector<double> dist;
		double distance = 0;
		std::vector<size_t> indices;
		auto bmu1 = new Point();
		auto bmu2 = new Point();
		Point bmu;
		for (size_t i = 0; i < this->train_data_size_; ++i)
		{
			indices.push_back(i);
		}
		try
		{
			for (size_t c_iteration = 0; c_iteration < this->iteration_max_; ++c_iteration)
			{
				std::random_shuffle(indices.begin(), indices.end());
				distance = 0;
				std::cout << "|=================================|" << std::endl;
				std::cout << std::left << std::setw(22) << std::setfill('_') << "|Iteration" << std::setw(12) << std::right << (c_iteration + 1) << "|" << std::endl;

				for (size_t t = 0; t < this->train_data_size_; ++t)
				{
					auto td = this->train_data_[indices[t]];
					//Point bmu = get_bmu(this->train_data[indices[t]]);
					std::thread th1(get_bmu_mt, td, 0, this->map_y_ / 2, this->map_, this->map_z_, this->map_x_, bmu1);
					std::thread th2(get_bmu_mt, td, this->map_y_ / 2 + 1, this->map_y_, this->map_, this->map_z_, this->map_x_, bmu2);
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
					auto idx = GetIndices(c_iteration, bmu);
					for (size_t i = 0; i < idx.size(); ++i)
						Train(this->train_data_[indices[t]], this->map_[idx[i].y][idx[i].x], static_cast<size_t>(idx[i].dist),
							c_iteration);
				}

				std::cout << std::left << std::setw(22) << "|Quantiziation Error" << std::setw(12) << std::right << std::setprecision(8) << (distance / this->train_data_size_) << "|" << std::endl;
				std::cout << std::left << std::setw(22) << "|Alpha" << std::setw(12) << std::right << std::setprecision(8) << this->alpha_values_[c_iteration] << "|" << std::endl;
				std::cout << std::left << std::setw(22) << "|Radius" << std::setw(12) << std::right << std::setprecision(8) << this->neighbor_radius_[c_iteration] << "|" << std::endl;
				dist.push_back(distance / this->train_data_size_);
			}
		} // c_iteration
		catch (...)
		{
			std::cout << "Shit happens" << std::endl;
		}
		auto dd = .0;
		auto mintr = 50.0;
		for (size_t i = 0; i < dist.size(); ++i)
		{
			dd += dist[i];
			mintr = mintr < dist[i] ? mintr : dist[i];
		}
		dd /= dist.size();
		std::cout << "|=================================|" << std::endl;

		std::cout << std::setw(22) << std::left
			<< "|Train Distance Avg" << std::setw(12) << std::right << std::setprecision(8) << dd << "|" << std::endl;
		std::cout << std::setw(22) << std::left
			<< "|Train Distance Min" << std::setw(12) << std::right << std::setprecision(8) << mintr << "|" << std::endl;
		std::cout << std::setw(22) << std::left
			<< "|Train Distance Last" << std::setw(12) << std::right << std::setprecision(8) << dist[dist.size() - 1] << "|" << std::endl;
		delete bmu1;
		delete bmu2;
		SaveMap();
		return this;
	}
	Som *Som::OpenMap(const char *source) {
		auto som = new Som();
		std::ifstream myFile;
		myFile.open(source, std::ios::in | std::ios::binary);
		myFile.read((char *)&som->map_x_, sizeof(som->map_x_));
		myFile.read((char *)&som->map_y_, sizeof(som->map_y_));
		myFile.read((char *)&som->map_z_, sizeof(som->map_z_));
		myFile.read((char *)&som->iteration_max_, sizeof(som->iteration_max_));
		myFile.read((char *)&som->train_data_size_, sizeof(som->train_data_size_));
		myFile.read((char *)&som->neighbor_start_, sizeof(som->neighbor_start_));
		myFile.read((char *)&som->alpha_, sizeof(som->alpha_));
		som->InitMap()->InitMap()->InitMap();
		for (size_t row = 0; row < som->map_y_; ++row)
			for (size_t col = 0; col < som->map_x_; ++col)
				for (size_t w = 0; w < som->map_z_; ++w)
				{
					myFile.read((char *)&som->map_[row][col][w], sizeof(som->map_[row][col][w]));
					std::cout << som->map_[row][col][w] << std::endl;
				}
		myFile.close();
		return som;
	}
	double Som::LatticeWidth(const size_t &iteration) {
		return this->neighbor_start_ * exp(-1 * (iteration / this->iteration_max_));
	}
	Som *Som::SaveMap() {
		std::ofstream myFile;
		myFile.open("som.som", std::ios::out | std::ios::binary);
		myFile.write((char *)&this->map_x_, sizeof(this->map_x_));
		myFile.write((char *)&this->map_y_, sizeof(this->map_y_));
		myFile.write((char *)&this->map_z_, sizeof(this->map_z_));
		myFile.write((char *)&this->iteration_max_, sizeof(this->iteration_max_));
		myFile.write((char *)&this->train_data_size_, sizeof(this->train_data_size_));
		myFile.write((char *)&this->neighbor_start_, sizeof(this->neighbor_start_));
		myFile.write((char *)&this->alpha_, sizeof(this->alpha_));

		for (size_t row = 0; row < this->map_y_; ++row)
			for (size_t col = 0; col < this->map_x_; ++col)
				for (size_t w = 0; w < this->map_z_; ++w)
				{
					myFile.write((char *)&this->map_[row][col][w], sizeof(this->map_[row][col][w]));
				}
		myFile.close();
		return this;
	}
	double Som::NeighborRate(const size_t &distance, const size_t &iteration) {
		double o = LatticeWidth(iteration);
		o *= o;
		return exp(-((distance * distance) / (2 * o)));
	}

	// Es wird ein Neuron trainiert, dabei ist dinstance der Abstand zum BMU
	Som *Som::Train(const double *v, double *w, const size_t &distance, const size_t &iteration) {
		double n_r = NeighborRate(distance, iteration);
		for (size_t i = 0; i < this->map_z_; ++i)
			w[i] = w[i] + n_r * this->alpha_values_[iteration] * (v[i] - w[i]);
		return this;
	}
	com_b_velop::Validation Som::Validation(const Set *set) {
		com_b_velop::Validation validation;
		double v = 0;
		std::vector<com_b_velop::ValidSet> vs;
		for (size_t row = 0; row < set->rows; ++row)
		{
			auto bmu = GetBmu(set->values[row]);
			ValidSet tmp;
			tmp.w = this->map_z_;
			for (size_t w = 0; w < tmp.w; ++w)
			{
				auto j = set->values[row][w];
				auto u = this->map_[bmu.y][bmu.x][w];
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
		std::cout << "|=================================|" << std::endl;
		std::cout << std::left << std::setw(22) << "|Validation Distance" << std::setprecision(8) << std::right << std::setw(12) << v << "|" << std::endl;
		std::cout << std::setw(22) << std::left << "|Test Data Size" << std::setw(12) << std::right << std::setprecision(8) << validation.valid_set.size() << "|" << std::endl;
		std::cout << "|=================================|" << std::endl;

		return validation;
	}
}
#pragma once
#include <cmath>
#include <string>
#include <vector>
#include "../SelfOrganizinMap.Infrastructure/types.hpp"
#include "../SelfOrganizinMap.Infrastructure/set.h"

namespace com_b_velop
{
	class Som
	{
	public:
		Som() :
			map_(nullptr),
			map_rdy_(false),
			map_x_(0),
			map_y_(0),
			map_z_(0),
			iteration_max_(2),
			train_data_size_(0),
			neighbor_start_(5),
			alpha_(.7),
			alpha_values_(nullptr),
			train_data_(nullptr),
			neighbor_radius_(nullptr) {	  }

		Som(size_t x, size_t y, size_t z);
		~Som();
		Som *SetTrainData(const std::vector<std::vector<double>> &in_train_data);
		Som *SetTrainData(const com_b_velop::Set *in_train_data);
		Som *SetAlpha(const double &in_alpha);
		Som *SetIterationMax(const size_t &in_iteration_max);
		Som *SetNeighborStart(const size_t &in_neighbor_start);
		Som *SetDimension(const size_t &rows, const size_t &columns);
		Som *StartTraining();
		Validation Validation(const Set *set);
		static Som *OpenMap(const char *source);

		double LearningInverseOfTime(unsigned long iteration)
		{
			return this->alpha_ * (1.0 - static_cast<double>(iteration) / static_cast<double>(this->iteration_max_));
		}
		double LearingPowerSeries(unsigned long iteration)
		{
			return this->alpha_ * exp(static_cast<double>(iteration) / static_cast<double>(this->iteration_max_));
		}
		// http://www.cis.hut.fi/somtoolbox/documentation/somalg.shtml
		// http://www.saedsayad.com/clustering_som.htm
		Som *Init();

	private:
		double ***map_;
		bool map_rdy_;
		size_t map_x_;
		size_t map_y_;
		size_t map_z_;
		size_t iteration_max_;
		size_t train_data_size_;
		size_t neighbor_start_;
		double alpha_;
		double *alpha_values_;
		double **train_data_;
		size_t *neighbor_radius_;
		std::vector<Point> GetIndices(const size_t &iteration, const Point &bmu) const;

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


		Som *InitNeighbor();

		/**
		 * Bmu Suche. Die Funktion durchläuft die gesamte und sucht das Neuron, was input am ähnlichsten ist.
		 * Die Koordinate und die Distanz werden in Point festgehalten.
		 * @param input Ein Vektor der eine Zeile aus den Trainingsdaten enthält
		 * @return Ein Point-Objekt mit den Koordinaten des BMU und der Distanz zum BMU
		 */
		Point GetBmu(const double *input);
		Som *SaveMap();
		// void get_bmu_mt(const double *input, const size_t &from, const size_t &to, Point &bmu);
		double LatticeWidth(const size_t &iteration);
		double NeighborRate(const size_t &distance, const size_t &iteration);
		double GetDistance(const double *v, const double *w, const size_t &n) const;
		Som *TrainBmu(size_t iteration, double *input, double *weight);
		double LearningLinear(const size_t &iteration) const;
		size_t GetNeighborRadius(const size_t &iteration) const;
		Som *Train(const double *v, double *w, const size_t &distance, const size_t &iteration);
	}; // Som
} // namespace com_b_velop

#pragma once
struct SomInfo
{
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
};

#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include "numcpp.h"

namespace utils {

	double bilateral_filter (double j, double t, double y_j, double y_t, double delta1 = 1.0, double delta2 = 1.0) {
		double idx1 = -1.0*(abs(j-t)*abs(j-t))/(2.0*delta1*delta1);
		double idx2 = -1.0*(abs(y_j-y_t)*abs(y_j-y_t))/(2.0*delta2*delta2);

		double weight = exp(idx1)*exp(idx2);
		return weight;
	}

	nc::tuple_d get_neighbor_idx (double total_len, double target_idx, int H = 3) {
		nc::tuple_d out;
		out.first = max(0, (int)target_idx-H); out.second = min(total_len, target_idx+H+1);
		return out;
	}

	nc::array get_neighbor_range (double total_len, double target_idx, int H = 3) {
		nc::tuple_d n_idx = get_neighbor_idx(total_len, target_idx, H);
		
		return nc::arange(n_idx.first, n_idx.second);
	}

	nc::array get_season_idx (double total_len, double target_idx, int T=10, int K=2, int H=5) {
		double num_season = min(K, (int)(target_idx/T));
		nc::array key_idxs;
		if(target_idx < T) 
			key_idxs = nc::add(target_idx, nc::mul(nc::arange(0, num_season+1), -1*T));
		else
			key_idxs = nc::add(target_idx, nc::mul(nc::arange(1, num_season+1), -1*T));

		nc::matrix idxs_mat;
		for(int i=0;i<key_idxs.size();i++)
			idxs_mat.push_back(get_neighbor_range(total_len, key_idxs[i], H));

		return nc::flatten(idxs_mat);
	}

	nc::array get_relative_trends (nc::array delta_trends) {
		nc::array init_value = nc::zeros(1);
		nc::array relative_trends; int prev = 0;
		for(int i=0;i<delta_trends.size();i++) {
			relative_trends.push_back(delta_trends[i] + prev); 
			prev = relative_trends[i];
		}
		return nc::concat(init_value, relative_trends);

	}

}

#endif
#ifndef ROBUST_STL_H
#define ROBUST_STL_H

#include "numcpp.h"

namespace stl {
	nc::array denoise_step (nc::array sample, int H=3, double dn1=1.0, double dn2=1.0) {

		struct internal {
			static double get_denoise_value (double idx, nc::array sample, int H, double dn1, double dn2) {
				nc::tuple_d se_idx = utils::get_neighbor_idx(sample.size(), idx, H);
				nc::array idxs = nc::arange(se_idx.first, se_idx.second);
				nc::array weight_sample;
				for(int i=0;i<idxs.size();i++)
					weight_sample.push_back(sample[idxs[i]]);
				nc::array weights;
				for(int i=0;i<idxs.size();i++)
					weights.push_back(utils::bilateral_filter(idxs[i],idx,sample[idxs[i]],sample[idx],dn1,dn2));
				return nc::sum(nc::mul(weight_sample, weights))/nc::sum(weights);
			}
		};

		nc::array denoise_sample;

		for(int i=0;i<sample.size();i++)
			denoise_sample.push_back(internal::get_denoise_value(i, sample, H, dn1, dn2));

		return denoise_sample;
	}

	nc::array seasonality_extraction (nc::array sample, int season_len=10, int K=2, int H=5, double ds1=50.0, double ds2=1.0) {
		struct internal {
			static double get_season_value (double idx, nc::array sample, int season_len, int K, int H, double ds1, double ds2) {
				nc::array idxs = utils::get_season_idx(sample.size(), idx, season_len, K, H);
				if(idxs.size() == 0) return sample[idx];
				nc::array weight_sample;
				for(int i=0;i<idxs.size();i++)
					weight_sample.push_back(sample[idxs[i]]);
				nc::array weights;
				for(int i=0;i<idxs.size();i++)
					weights.push_back(utils::bilateral_filter(idxs[i],idx,sample[idxs[i]],sample[idx],ds1,ds2));
				return nc::sum(nc::mul(weight_sample, weights))/nc::sum(weights);
			}
		};

		nc:: array season_tilda;
		for(int i=0;i<sample.size();i++)
			season_tilda.push_back(internal::get_season_value(i,sample,season_len,K,H,ds1,ds2));
		return season_tilda;
	}
}

#endif
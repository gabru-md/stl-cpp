#ifndef ROBUST_STL_H
#define ROBUST_STL_H

#include <time.h>
#include <stdlib.h>

#include "numcpp.h"
#include "utils.h"
// #include "l1_norm.h"

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

				nc::RELEASE_MEM(idxs);

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

	nc::tuple_tri adjustment (nc::array sample, nc::array relative_trends, nc::array season_tilda, int season_len) {
		int num_season = (int)sample.size()/season_len;
		double trend_init = nc::mean(nc::slice(season_tilda, 0, season_len*num_season));
		nc::array trends_hat = nc::add(relative_trends, trend_init);
		nc::array seasons_hat = nc::sub(season_tilda, trend_init);
		nc::array remainders_hat = nc::sub(nc::sub(sample, trends_hat), seasons_hat);
		nc::tuple_tri out = {trends_hat, seasons_hat, remainders_hat};
		return out;
	}

	 bool check_converge_criteria (nc::array prev_remainders, nc::array remainders) {
		double diff = std::sqrt(nc::mean(nc::square(nc::sub(remainders, prev_remainders))));
		if(diff < 1e-10)
			return true;
		return false;
	}

	nc::tuple_a trend_extraction (nc::array sample, int season_len, double reg1=10.0, double reg2=0.5) {
		int sample_len = sample.size();
		nc::array season_diff = nc::sub(nc::slice(sample, season_len), nc::rev_slice(sample, 0, season_len));
		nc::array q_arr = nc::concat(season_diff, nc::zeros(sample_len*2-3));
		std::cout << q_arr;
		nc::matrix q = nc::reshape(q_arr, nc::shape(q_arr.size(), 1));
		std::cout << q << std::endl;

		nc::matrix M = tz::get_toeplitz(nc::shape(sample_len-season_len,sample_len-1), nc::ones(season_len));
		nc::array bipolar; bipolar.push_back(1); bipolar.push_back(-1);
		nc::matrix D = tz::get_toeplitz(nc::shape(sample_len-2, sample_len-1), bipolar);
		nc::matrix P = nc::concat(M, nc::mul(reg1, nc::eye(sample_len-1)), nc::mul(reg2, D)); // write concatenate function here => np.concatenate([M, reg1*np.eye(sample_len-1), reg2*D], axis=0)
		std::cout << P.size() << " : " << P[0].size() << std::endl;
		//std::cout << P;
		nc::array delta_trends;// = l1::py_L1(P,q);
		std::cout << delta_trends;
		nc::array relative_trends = utils::get_relative_trends(delta_trends);

		return nc::tuple_a(nc::sub(sample, relative_trends), relative_trends);
	}

	nc::array get_sample(int sample_size, int season_len) {
		nc::array out; int k = sample_size/season_len; int j = 100; int up=true;
		//std::cout<<k<<std::endl;
		srand (time(NULL));
		for(int i=0;i<sample_size;i++) {
			out.push_back(j);
			if(up)
				j = j + (rand()%10);
			else
				j = j - (rand()%10);
			if(i%(k/2)==0) {
				up = !up;
			}
			if(i%k==0) {
				j += (rand()%1000);
			}
		}
		return out;
	}
}

#endif
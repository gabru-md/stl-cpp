/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"
#include "include/utils.h"
#include "include/robust_stl.h"
#include "include/iqr.h"
#include "include/matplotlibcpp.h"

#include <iostream>
#include <iterator>
#include <cstdlib>

namespace plt = matplotlibcpp;

nc::anomaly anomalize_iqr(nc::array sample, int season_len) {
	nc::tuple_quad res = stl::RobustSTL(nc::log_(sample), season_len);
	nc::anomaly isAnomaly = iqr::findIQROutliers(res.fourth);
	return isAnomaly;
}

int main(void) {
	nc::array sample;
	double arr [] = {200,210,300,250,400,500,550,780,1100,1632,321,200,350,400,430,489,424,612,732,770,900,1400,1802,532,402,423};
	for(int i=0;i<(sizeof(arr)/sizeof(arr[0]));i++) {
		sample.push_back(arr[i]);
	}
	std::cout << sample.size() << std::endl;
	//nc::array sample;
	// sample.push_back(1);sample.push_back(2);sample.push_back(3);sample.push_back(4);sample.push_back(2);sample.push_back(3);sample.push_back(120);sample.push_back(21);sample.push_back(3);sample.push_back(4);
	// sample length is the length of consecutive data points that make a season
	nc::tuple_quad res = stl::RobustSTL(nc::log_(sample), 13);
	nc::flush("sample", sample);
	nc::flush("input", res.first);
	nc::flush("trends_hat", res.second);
	nc::flush("seasons_hat", res.third);
	nc::flush("remainders_hat", res.fourth);

	// nc::flush("log.seasonal", nc::log_(res.third));
	// nc::flush("log.expected = log.seasonal + log.trend", nc::add(nc::log_(res.third), nc::log_(res.second)));
	// nc::flush("log.observed", nc::log_(res.first));

	nc::anomaly isAnomaly = iqr::findIQROutliers(res.fourth);
	nc::flush("anomalies in remainder", isAnomaly, sample);

	plt::plot(sample);
	plt::show();

	isAnomaly = iqr::findIQROutliers(sample);
	nc::flush("anomalies in sample", isAnomaly);

	return 0;
}

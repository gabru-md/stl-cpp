/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"
#include "include/utils.h"
#include "include/robust_stl.h"
#include "include/iqr.h"

#include <iostream>
#include <cstdlib>

int main(void) {
	nc::array sample;
	sample.push_back(1);sample.push_back(2);sample.push_back(3);sample.push_back(4);sample.push_back(2);sample.push_back(3);sample.push_back(120);sample.push_back(21);sample.push_back(3);sample.push_back(4);
	nc::tuple_quad res = stl::RobustSTL(sample, 2);
	nc::flush("input", res.first);
	nc::flush("trends_hat", res.second);
	nc::flush("seasons_hat", res.third);
	nc::flush("remainders_hat", res.fourth);

	nc::anomaly isAnomaly = iqr::findIQROutliers(res.fourth);
	nc::flush("anomalies in remainder", isAnomaly);

	isAnomaly = iqr::findIQROutliers(sample);
	nc::flush("anomalies in sample", isAnomaly);

	return 0;
}

#ifndef IQR_H
#define IQR_H

#include <algorithm>
#include "numcpp.h"
#include <iostream>

//uses IQR - Inter Quartile Range to find outliers.
namespace iqr {

	struct tuple_tri {
		double Q1;
		double Q3;
		double IQR;
	};

	int median (nc::array in, int low, int high) {
		int n = high - low + 1; 
	    n = (n + 1) / 2 - 1; 
	    return n + low; 
	}

	bool inRange(double el, double low, double high) {
		return (el>=low && el<=high);
	}

	tuple_tri _iqr (nc::array in) {

		nc::array sample = in;
		int n = sample.size();

		sort(sample.begin(), sample.end());
		int mid_index = median(sample, 0, n);

		double Q1 = sample[median(sample, 0, mid_index)];
		double Q3 = sample[median(sample, mid_index+1, n)];

		double _iqr = Q3-Q1;

		tuple_tri toReturn = {Q1, Q3, _iqr};

		return toReturn;
	}

	nc::anomaly findIQROutliers (nc::array sample) {
		nc::anomaly toReturn(sample.size(), false);
		tuple_tri res = _iqr(sample);
		std::cout << res.Q1 <<" : " << res.Q3 << " : " << res.IQR << std::endl << std::endl;
		std::cout << res.Q1-1.5*res.IQR << " : "<< res.Q3+1.5*res.IQR<< std::endl << std::endl;
		for(int i=0;i<sample.size();i++) {
			if(inRange(sample[i], res.Q1-1.5*res.IQR, res.Q3+1.5*res.IQR))
				continue;
			toReturn[i] = true;
		}

		return toReturn;
	}

}

#endif
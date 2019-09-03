#ifndef TOEPLITZ_H
#define TOEPLITZ_H

#include "numcpp.h"

// computes toeplitz matrix from arrays
namespace tz {

	nc::matrix toeplitz (nc::array c, nc::array r) {
		c = nc::flatten(c); r = nc::flatten(r);
		nc::od_array _c (c, -1);
		nc::array vals = nc::concat(_c,r,1);
		nc::array toep_arr = nc::slice(vals, c.size() - 1);
		nc::shape shp (c.size(), r.size());
		nc::matrix toep_mat = nc::ncmat(shp);
		for(int i=0;i<shp.first;i++) {
			for(int j=i;j<shp.second;j++)
				toep_mat[i][j] = toep_arr[j-i];
			for(int j=0;j<i;j++)
				toep_mat[i][j] = toep_arr[shp.second - i];
		}
		return toep_mat;
	}
	nc::matrix toeplitz (nc::array c, nc::matrix r) {
		return toeplitz(c, nc::flatten(r));
	}

	nc::matrix toeplitz (nc::matrix c, nc::matrix r) {
		return toeplitz(nc::flatten(c), nc::flatten(r));
	}

	nc::matrix toeplitz (nc::matrix c, nc::array r) {
		return toeplitz(nc::flatten(c), r);
	}

}

#endif
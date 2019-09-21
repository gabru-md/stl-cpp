#ifndef TOEPLITZ_H
#define TOEPLITZ_H

#include "numcpp.h"
#include <iostream>

// computes toeplitz matrix from arrays
namespace tz {

	nc::matrix toeplitz (nc::array c, nc::array r) {
		// c as first column and r as first row


		c = nc::flatten(c); r = nc::flatten(r);
		nc::shape shp (c.size(), r.size());
		nc::matrix toep_mat = nc::ncmat(shp);

		for(int j=0;j<shp.second;j++)
			toep_mat[0][j] = r[j];
		for(int i=0;i<shp.first;i++)
			toep_mat[i][0] = c[i];

		for(int i=1;i<shp.first;i++) {
			for(int j=i;j<shp.second;j++)
				toep_mat[i][j] = r[j-i];
			for(int j=0;j<i;j++)
				toep_mat[i][j] = c[shp.second - i];
		}
		
		nc::RELEASE_MEM(c); nc::RELEASE_MEM(r);

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

	nc::matrix get_toeplitz (nc::shape shp, nc::array entry) {
		int h = shp.first; int w = shp.second;
		int num_entry = entry.size();
		if(num_entry < 1)
			return nc::zeros(shp);
		nc::array row = nc::concat(entry[0], nc::zeros(h-1));
		nc::array col = nc::concat(nc::flatten(entry), nc::zeros(w-num_entry));
		return toeplitz(row, col);
	}

}

#endif
#ifndef TOEPLITZ_H
#define TOEPLITZ_H

#include <iostream>
#include "numcpp.h"

// computes toeplitz matrix from arrays
namespace tz {
	
	nc::matrix toeplitz (nc::array c, nc::array r) {
		c = nc::flatten(c); r = nc::flatten(r);
		nc::odarray _c (c, -1);
		nc::array vals = nc::concat(_c,r,1);
		

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
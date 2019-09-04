/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"
#include "include/utils.h"
#include <iostream>

int main(void) {
	// nc::shape shp (3,4);
	// nc::array entry (3,0); entry[0] = 5; entry[1] = 2; entry[2] = 4;
	// nc::matrix op = tz::get_toeplitz(shp, entry);
	// nc::flush(op);
	nc::flush << util::get_season_idx(32,14);
	std::cout <<  std::endl ;
	std::cout << util::bilateral_filter(3.2,2.1,4.3,3.2) << std::endl;
	return 0;
}
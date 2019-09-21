/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"
#include "include/utils.h"
#include "include/robust_stl.h"

#include <iostream>
#include <cstdlib>

int main(void) {
	nc::tuple_quad res = stl::RobustSTL(stl::get_sample(50,2), 2);
	nc::flush("input", res.first);
	nc::flush("trends_hat", res.second);
	nc::flush("seasons_hat", res.third);
	nc::flush("remainders_hat", res.fourth);
	return 0;
}

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
	stl::trend_extraction(stl::get_sample(10,2), 2);
	return 0;
}

/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"
#include "include/utils.h"
#include "include/robust_stl.h"
// #include "include/l1_norm.h"
#include "l1/l1qc_test.h"

#include <iostream>
#include <cstdlib>


// void solve() {

// }

int main(void) {
	setenv("PYTHONPATH",".",1);
	stl::trend_extraction(stl::get_sample(40,2), 2);
	return 0;
	
}

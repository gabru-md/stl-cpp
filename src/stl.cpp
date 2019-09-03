/*
 * created by : gabru-md
 */

#include "include/numcpp.h"
#include "include/toeplitz.h"

int main(void) {
	nc::shape s (2,3);
	nc::matrix m = nc::ncmat(s);
	m[0][0]=0; m[0][1]=1;m[0][2]=2;m[1][1]=1;m[1][0]=1;m[1][2]=3;
	nc::array a(4); nc::array b(3);
	b[0]=9;b[1]=5;b[2]=3;
	a[0]=1;a[1]=9;a[2]=7;a[3]=5;
	nc::matrix op = tz::toeplitz(a,b);
	nc::flush(op);
	return 0;
}
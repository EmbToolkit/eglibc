#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

int main() {
	TEST_i_f_all(ilogb,-3, 0.0023);
	TEST_i_f_all(ilogb,-2, 0.023);
	TEST_i_f_all(ilogb,-1, 0.23);
	TEST_i_f_all(ilogb,-1, -0.23);
	TEST_i_f_all(ilogb,-3, -0.0023);
	TEST_i_f_all(ilogb,0, 2.30);
	TEST_i_f_all(ilogb,1, 23.0);
}


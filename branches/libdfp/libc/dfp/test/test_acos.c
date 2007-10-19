#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

int main() {
	TEST_f_f_all(acos, 0.722734247813415611178377352641333362, 0.75);
}


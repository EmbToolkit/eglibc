#include <stdio.h>
#include <stdint.h>

#ifndef __STDC_WANT_DEC_FP__
#define __STDC_WANT_DEC_FP__ 1
#endif

#include <fenv.h>
#include <math.h>

#define D32ZERO 0.0DF;
#define D64ZERO 0.0DD;
#define D128ZERO 0.0DL;

void fpc(int i) {
	switch (i) {
	  case FP_NAN:
	    printf("value is FP_NAN\n");
	    break;
	  case FP_INFINITE:
	    printf("value is FP_INFINITE\n");
	    break;
	  case FP_ZERO:
	    printf("value is FP_ZERO\n");
	    break;
	  case FP_SUBNORMAL:
	    printf("value is FP_SUBNORMAL\n");
	    break;
	  case FP_NORMAL:
	    printf("value is FP_NORMAL\n");
	    break;
	default:
	    printf("value is unknown\n");
	}
}

int main() {

	_Decimal32 dnan32 = DEC_NAN;
	_Decimal32 dinf32 = DEC_INFINITY;
	_Decimal32 dzero32 = D32ZERO;
	_Decimal32 dnormal32 = 2.3DF;
	_Decimal32 dsub = 1.0e-100DF;
	_Decimal32 min = 1.0e-95DF;
	_Decimal32 trickynormal = 10.0e-96DF;
	_Decimal32 justdenormal = 1.0e-96DF;

	fpc(fpclassify(dnan32));
	fpc(fpclassify(dinf32));
	fpc(fpclassify(dzero32));
	fpc(fpclassify(dnormal32));
	fpc(fpclassify(dsub));
	fpc(fpclassify(min));
	fpc(fpclassify(trickynormal));
	fpc(fpclassify(justdenormal));
}

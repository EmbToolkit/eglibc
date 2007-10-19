#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>
#include <fenv.h>

void nearby(void) {
	_Decimal32 d32;
	_Decimal32 nbd32;

	_Decimal64 d64;
	_Decimal64 nbd64;

	_Decimal128 d128;
	_Decimal128 nbd128;

	d32 = 19.54DF;
	d64 = 19.54DD;
	d128 = 19.54DL;

	nbd32 = nearbyintd32(d32);
	printf(" %Hf = nearbyintd32(  %Hf)\n", nbd32, d32);
	d32 = -19.54DF;
	nbd32 = nearbyintd32(d32);
	printf("%Hf = nearbyintd32( %Hf)\n", nbd32, d32);

	nbd64 = nearbyintd64(d64);
	printf(" %Df = nearbyintd64(  %Df)\n", nbd64, d64);
	d64 = -19.54DD;
	nbd64 = nearbyintd64(d64);
	printf("%Df = nearbyintd64( %Df)\n", nbd64, d64);

	nbd128 = nearbyintd128(d128);
	printf(" %DDf = nearbyintd128( %DDf)\n", nbd128, d128);
	d128 = -19.54DL;
	nbd128 = nearbyintd128(d128);
	printf("%DDf = nearbyintd128(%DDf)\n", nbd128, d128);
}

int main() {

	int round = 0;

	printf("*** Default rounding mode is FE_DEC_TONEAREST\n", round );
	nearby();

	printf ("*** Changing rounding mode to FE_DEC_TOWARDZERO\n");
	round = fe_dec_setround(FE_DEC_TOWARDZERO);
	nearby();

	printf ("*** Changing rounding mode to FE_DEC_UPWARD\n");
	round = fe_dec_setround(FE_DEC_UPWARD);
	nearby();

	printf ("*** Changing rounding mode to FE_DEC_TONEARESTFROMZERO\n");
	round = fe_dec_setround(FE_DEC_TONEARESTFROMZERO);
	nearby();

	printf ("*** Changing rounding mode to FE_DEC_DOWNWARD\n");
	round = fe_dec_setround(FE_DEC_DOWNWARD);
	nearby();
}

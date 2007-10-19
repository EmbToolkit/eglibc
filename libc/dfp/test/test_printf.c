#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

int main() {

        _Decimal32 d32;
	_Decimal64 d64;
	_Decimal128 d128;
	_Decimal128 e128;
	_Decimal128 f128;
	float f32;

	d32 = 349.23456923482E27DF;
	printf("349.23456923482E27DF\n");
	printf("_Decimal32 Scientific:  %Hf\n", d32);
	printf("_Decimal32 Engineering: %He\n", d32);
	printf("\n");

	d32 = 349E27DF;
	printf("349E27DF\n");
	printf("_Decimal32 Scientific:  %Hf\n", d32);
	printf("_Decimal32 Engineering: %He\n", d32);
	printf("\n");

	d64 = 349.1231115DD;
	printf("349.1231115DD\n");
	printf("_Decimal64 Scientific:  %Df\n", d64);
	printf("_Decimal64 Enginerring:  %De\n", d64);
	printf("_Decimal64 with format flags:\n");
	printf("  %%.3Df:    '%.3Df'\n", d64);
	printf("  %%12.3Df:  '%12.3Df'\n", d64);
	printf("  %%-12.3Df: '%-12.3Df'\n", d64);
	printf("\n");

	d128 = 1.2315DL;
	printf("1.2315DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("_Decimal128 Engineering: %DDe\n", d128);
	printf("_Decimal128 with format flags:\n");
	printf("  %%.3DDf:    '%.3DDf'\n", d128);
	printf("  %%12.3DDf:  '%12.3DDf'\n", d128);
	printf("  %%-12.3DDf: '%-12.3DDf'\n", d128);
	printf("\n");

	d128 = 231.2315DL;
	printf("231.2315DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("_Decimal128 Engineering: %DDe\n", d128);
	printf("_Decimal128 with format flags:\n");
	printf("  %%.3DDf:    '%.3DDf'\n", d128);
	printf("  %%12.3DDf:  '%12.3DDf'\n", d128);
	printf("  %%-12.3DDf: '%-12.3DDf'\n", d128);
	printf("\n");

	d128 = 0.12315DL;
	printf("0.12315DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("_Decimal128 Engineering: %DDe\n", d128);
	printf("_Decimal128 with format flags:\n");
	printf("  %%.4DDf:    '%.4DDf'\n", d128);
	printf("  %%12.4DDf:  '%12.4DDf'\n", d128);
	printf("  %%-12.4DDf: '%-12.4DDf'\n", d128);
	printf("\n");

	d128 = -0.12315DL;
	printf("-0.12315DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("_Decimal128 Engineering: %DDe\n", d128);
	printf("_Decimal128 with format flags:\n");
	printf("  %%.4DDf:    '%.4DDf'\n", d128);
	printf("  %%12.4DDf:  '%12.4DDf'\n", d128);
	printf("  %%-12.4DDf: '%-12.4DDf'\n", d128);
	printf("\n");


	d128 = 0.012315DL;
	printf("0.012315DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("_Decimal128 Engineering: %DDe\n", d128);
	printf("_Decimal128 with format flags:\n");
	printf("  %%.3DDf:    '%.3DDf'\n", d128);
	printf("  %%.4DDf:    '%.4DDf'\n", d128);
	printf("  %%.5DDf:    '%.5DDf'\n", d128);
	printf("  %%12.5DDf:  '%12.5DDf'\n", d128);
	printf("  %%-12.5DDf: '%-12.5DDf'\n", d128);
	printf("  %%-12DDf: '%-12DDf'\n", d128);

	d128 = 0.012315E7DL;
	printf("0.012315E7DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("_Decimal128 Engineering: %DDe\n", d128);
	printf("_Decimal128 with format flags:\n");
	printf("  %%.3DDf:    '%.3DDf'\n", d128);
	printf("  %%.4DDf:    '%.4DDf'\n", d128);
	printf("  %%.5DDf:    '%.5DDf'\n", d128);
	printf("  %%13.5DDf:  '%13.5DDf'\n", d128);
	printf("  %%-13.5DDf: '%-13.5DDf'\n", d128);
	printf("  %%-13DDf: '%-13DDf'\n", d128);

	d128 = -0.012315E7DL;
	printf("-0.012315E7DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.3DDf:    '%.3DDf'\n", d128);
	printf("  %%.4DDf:    '%.4DDf'\n", d128);
	printf("  %%.5DDf:    '%.5DDf'\n", d128);

	d128 = -0.012315E-7DL;
	printf("-0.012315E-7DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);

	d128 = 1231.5E27DL;
	printf("1231.5E27DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);

	d128 = 1231.5E26DL;
	printf("1231.5E26DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);

	d128 = 12.365DL;
	printf("12.365DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);

	d128 = -12.365DL;
	printf("-12.365DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);

	d128 = -12.375DL;
	printf("-12.375DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);

	d128 = 12.375DL;
	printf("12.375DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);

	d128 = DEC_NAN;
	printf("DEC_NAN\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);
	printf("  %%12.3DDf:    '%12.3DDf'\n", d128);
	printf("  %%-12.3DDf:    '%-12.3DDf'\n", d128);

	d128 = DEC_INFINITY;
	printf("INF\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);
	printf("  %%12.3DDf:    '%12.3DDf'\n", d128);
	printf("  %%-12.3DDf:    '%-12.3DDf'\n", d128);

	d128 = -DEC_INFINITY;
	printf("-INF\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%.2DDf:    '%.2DDf'\n", d128);
	printf("  %%.8DDf:    '%.8DDf'\n", d128);
	printf("  %%.9DDf:    '%.9DDf'\n", d128);
	printf("  %%.10DDf:    '%.10DDf'\n", d128);
	printf("  %%12.3DDf:    '%12.3DDf'\n", d128);
	printf("  %%-12.3DDf:    '%-12.3DDf'\n", d128);


	d128 = 99999999999999.99999999999DL;
	printf("99999999999999.99999999999DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%30.1DDf:     '%30.1DDf'\n", d128);
	printf("  %%30.2DDf:     '%30.2DDf'\n", d128);
	printf("  %%30.3DDf:     '%30.3DDf'\n", d128);
	printf("  %%30.4DDf:     '%30.4DDf'\n", d128);
	printf("  %%30.5DDf:     '%30.5DDf'\n", d128);
	printf("  %%30.6DDf:     '%30.6DDf'\n", d128);
	printf("  %%30.7DDf:     '%30.7DDf'\n", d128);
	printf("  %%30.8DDf:     '%30.8DDf'\n", d128);
	printf("  %%30.9DDf:     '%30.9DDf'\n", d128);
	printf("  %%30.10DDf:    '%30.10DDf'\n", d128);
	printf("  %%30.11DDf:    '%30.11DDf'\n", d128);
	printf("  %%30.12DDf:    '%30.12DDf'\n", d128);
	printf("  %%30.13DDf:    '%30.13DDf'\n", d128);

	d128 = 9.999DL;
	printf("9.999DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%10.1DDf:     '%10.1DDf'\n", d128);
	printf("  %%10.2DDf:     '%10.2DDf'\n", d128);
	printf("  %%10.3DDf:     '%10.3DDf'\n", d128);
	printf("  %%10.4DDf:     '%10.4DDf'\n", d128);
	printf("  %%10.5DDf:     '%10.5DDf'\n", d128);

	d128 = 99999999999999.99999999999999999999DL;
	printf("99999999999999.99999999999999999999DL\n");
	printf("_Decimal128 Scientific:  %DDf\n", d128);
	printf("  %%30.1DDf:     '%30.1DDf'\n", d128);
	printf("  %%30.2DDf:     '%30.2DDf'\n", d128);
	printf("  %%30.3DDf:     '%30.3DDf'\n", d128);
	printf("  %%30.4DDf:     '%30.4DDf'\n", d128);
	printf("  %%30.5DDf:     '%30.5DDf'\n", d128);
	printf("  %%30.6DDf:     '%30.6DDf'\n", d128);
	printf("  %%30.7DDf:     '%30.7DDf'\n", d128);
	printf("  %%30.8DDf:     '%30.8DDf'\n", d128);
	printf("  %%30.9DDf:     '%30.9DDf'\n", d128);
	printf("  %%30.10DDf:    '%30.10DDf'\n", d128);
	printf("  %%30.11DDf:    '%30.11DDf'\n", d128);
	printf("  %%36.20DDf:    '%36.20DDf'\n", d128);
	printf("  %%36.21DDf:    '%36.21DDf'\n", d128);

	d32 = 999.9999DF;
	printf("999.999999DF\n");
	printf("_Decimal32 Scientific:  %Hf\n", d32);
	printf("_Decimal32 Engineering: %He\n", d32);
	printf("  %%16.3Hf:      '%16.3Hf'\n", d32);
	printf("  %%16.4Hf:      '%16.4Hf'\n", d32);
	printf("  %%16.5Hf:      '%16.5Hf'\n", d32);
	printf("\n");

	d32 = 999.999999DF;
	printf("999.999999DF\n");
	printf("_Decimal32 Scientific:  %Hf\n", d32);
	printf("_Decimal32 Engineering: %He\n", d32);
	printf("  %%16.3Hf:      '%16.3Hf'\n", d32);
	printf("\n");

        return -1;
}

/*#define __STDC_WANT_DEC_FP__ */
#include <float.h>
#include <math.h>
#include <stdio.h>

int main() {
	_Decimal32 d32;
	_Decimal64 d64;
	_Decimal128 d128;

	d32 = 2.7182818284590452353602874713526625DL;
	printf ("M_EDF = %Hf\n", d32);

	d64 = 2.7182818284590452353602874713526625DL;
	printf ("M_EDF = %Df\n", d64);

	d128 = 2.7182818284590452353602874713526625DL;
	printf ("M_EDF = %DDf\n", d128);

	d128 = 2.718281828459045235360287471352662DL;
	printf ("M_EDF = %DDf\n", d128);

	d128 = 2.7182818284590452353602874713526626DL;
	printf ("M_EDF = %DDf\n", d128);

	d32 = 0.0DL;

	if (d32 == 0.0DL)
	  printf ("(d32 = 0.0DL) == 0.0DL\n");
	else
	  printf ("Not\n");

	d32 = 0.0;

	printf ("(d32 = 0.0) == %Hf\n",d32);

	d32 = 0.0DL;

	printf ("d32  == %Hf\n",d32);

	d32 = 1.0DL;

	printf ("d32  == %Hf\n",d32);
	return 0;
}

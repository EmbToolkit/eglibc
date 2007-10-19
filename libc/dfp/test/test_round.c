#include <stdio.h>
#include <stdint.h>

#define __STDC_WANT_DEC_FP__ 1
#include <fenv.h>

static void print_roundingmode(int rounding_mode) {
	switch(rounding_mode)
	  {
	    case 0:
	      printf ("[%d] FE_DEC_TONEAREST(DEFAULT) = fe_dec_getround()\n", rounding_mode);
	      break;
	    case 1:
	      printf ("[%d] FE_DEC_TOWARDZERO = fe_dec_getround()\n", rounding_mode);
	      break;
	    case 2:
	      printf ("[%d] FE_DEC_UPWARD = fe_dec_getround()\n", rounding_mode);
	      break;
	    case 3:
	      printf ("[%d] FE_DEC_DOWNWARD = fe_dec_getround()\n", rounding_mode);
	      break;
	    case 4:
	      printf ("[%d] FE_DEC_TONEARESTFROMZERO = fe_dec_getround()\n", rounding_mode);
	      break;
	    case 5:
	      printf ("[%d] Round to nearest, ties toward zero = fe_dec_getround()\n", rounding_mode);
	      break;
	    case 6:
	      printf ("[%d] Round away from zero = fe_dec_getround()\n", rounding_mode);
	      break;
	    case 7:
	      printf ("[%d] Round for prepare for shorter precision = fe_dec_getround()\n", rounding_mode);
	      break;
	    default:
	      printf ("[%d] UNKNOWN = fe_dec_getround()\n",rounding_mode);
	      break;
	  }
}

int main() {
	int round, result = -1;
	printf ("Query default rounding mode:\n", round);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(FE_DEC_TOWARDZERO);
	printf ("%d = fe_dec_setround(FE_DEC_TOWARDZERO);\n", result);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(FE_DEC_TONEAREST);
	printf ("%d = fe_dec_setround(FE_DEC_TONEAREST);\n", result);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(FE_DEC_DOWNWARD);
	printf ("%d = fe_dec_setround(FE_DEC_DOWNWARD);\n", result);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(FE_DEC_UPWARD);
	printf ("%d = fe_dec_setround(FE_DEC_UPWARD);\n", result);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(FE_DEC_TONEARESTFROMZERO);
	printf ("%d = fe_dec_setround(FE_DEC_TONEARESTFROMZERO);\n", result);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(5);
	printf ("%d = fe_dec_setround(5);\n", result);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(6);
	printf ("%d = fe_dec_setround(6);\n", result);
	print_roundingmode(fe_dec_getround());

	result = fe_dec_setround(7);
	printf ("%d = fe_dec_setround(7);\n", result);
	print_roundingmode(fe_dec_getround());
}

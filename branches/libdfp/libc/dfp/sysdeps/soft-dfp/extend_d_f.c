








#include "convert.h"

extern double __truncdddf (_Decimal64);
extern _Decimal64 __extenddfdd (double);

DEST_TYPE
__extendddxf (SRC_TYPE a)
{
	double df_part1, df_part2;
	DEST_TYPE result;
	SRC_TYPE dd_part1, dd_part2;

	df_part1 = __truncdddf(a);		//_D64 -> dbl
	if(isnan(df_part1) || isinf(df_part1))
		return df_part1;		//inf or NaN
	dd_part1 = __extenddfdd(df_part1);	//dbl	-> _D64 (exact?)
	dd_part2 = a - dd_part1;		//_D64
	df_part2 = __truncdddf(dd_part2);	//_D64 -> dbl (trunc)
	result = df_part1;
	result += df_part2;
	return df_part1;
}

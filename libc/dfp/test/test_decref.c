#ifndef __STDC_WANT_DEC_FP__
#define __STDC_WANT_DEC_FP__
#endif

#include <stdio.h>

void function(_Decimal32 *d)
{
	_Decimal32 *e;
	_Decimal32 f;
	e = d;
	f = *e;
	printf("f == %Hf\n",f);
}

int main() {
	_Decimal32 d32 = 23.234E12DF;
	printf("d32 == %Hf\n", d32);
	printf("Calling 'function'.\n");
	function(&d32);

	return 0;
}

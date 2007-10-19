#ifndef __STDC_WANT_DEC_FP__
#define __STDC_WANT_DEC_FP__
#endif

#include <math.h>
#include <stdio.h>

int main() {
	_Decimal32 d32 = 1.2345df;
	_Decimal32 a32;
	int exp;

	a32 = frexpd32(d32,&exp);
	printf("%Hf = frexpd32(%Hf,&[%d])\n",a32,d32,exp);

	d32 = 12.324df;
	a32 = frexpd32(d32,&exp);
	printf("%Hf = frexpd32(%Hf,&[%d])\n",a32,d32,exp);

	d32 = 0.12315df;
	a32 = frexpd32(d32,&exp);
	printf("%Hf = frexpd32(%Hf,&[%d])\n",a32,d32,exp);

	d32 = 0.012315df;
	a32 = frexpd32(d32,&exp);
	printf("%Hf = frexpd32(%Hf,&[%d])\n",a32,d32,exp);

	d32 = 0.012315E12df;
	a32 = frexpd32(d32,&exp);
	printf("%Hf = frexpd32(%Hf,&[%d])\n",a32,d32,exp);

	d32 = 0.0123155E7df;
	a32 = frexpd32(d32,&exp);
	printf("%Hf = frexpd32(%Hf,&[%d])\n",a32,d32,exp);

	d32 = 123.123155E-7df;
	a32 = frexpd32(d32,&exp);
	printf("%Hf = frexpd32(%Hf,&[%d])\n",a32,d32,exp);
}

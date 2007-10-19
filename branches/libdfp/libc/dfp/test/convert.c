#include <stdio.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif

typedef	union {
		_Decimal64 d;
		long l[2];
	} convert;

int main() {


	convert c;
	convert d;
	convert e;
	convert f;
//	c.l[0] = 573833216L;
//	c.l[1] = 5120;

	c.l[0] = 0x22340000;
	c.l[1] = 0x00000050;


	d.l[0] = 0x223c0000;
	d.l[1] = 0x00000050;

	e.l[0] = 0x22340000;
	e.l[1] = 0x00001400;

	f.l[0] = 0x223c0000;
	f.l[1] = 0x00000051;

	printf("0x%.8x%.8x = %De\n",c.l[0], c.l[1], c.d);
	printf("0x%.8x%.8x = %De\n",d.l[0], d.l[1], d.d);
	printf("0x%.8x%.8x = %De\n",e.l[0], e.l[1], e.d);
	printf("0x%.8x%.8x = %De\n",f.l[0], f.l[1], f.d);

	return 0;
}

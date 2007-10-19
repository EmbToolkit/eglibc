#include <stdio.h>
#include <stdint.h>
#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>

#ifndef FUNCTION
#define FUNCTION isfinite
#endif

#define FUNCTION_CALL(type)	PASTE(FUNCTION,type)
#define PASTE(x,y)	PASTE1(x,y)
#define PASTE1(x,y)	x##y

#define DEC_INFINITYDF	DEC_INFINITY
#define DEC_INFINITYDD	(_Decimal64)DEC_INFINITY
#define DEC_INFINITYDL	(_Decimal128)DEC_INFINITY
int main() {
	_Decimal32 d32;
	_Decimal64 d64;
	_Decimal128 d128;
	int finite;

	d32 = -1.20DF;
	/* finite = FUNCTION_CALL()(d32); */
	finite = isfinite(d32);
	printf("%d = isfinite(%Hf)\n", finite, d32);
	/*printf("%d = __finited32(%Hf)\n", __finited32(d32), d32); */

	d32 = DEC_INFINITY;
	/* finite = FUNCTION_CALL()(d32); */
	finite = isfinite(d32);
	printf("%d = isfinite(%Hf)\n", finite, d32);
	/*printf("%d = __finited32(%Hf)\n", __finited32(d32), d32); */

	d32 = DEC_INFINITYDF;
	/* finite = FUNCTION_CALL()(d32); */
	finite = isfinite(d32);
	printf("%d = isfinite(%Hf)\n", finite, d32);
	/*printf("%d = __finited32(%Hf)\n", __finited32(d32), d32); */

	d32 = -DEC_INFINITYDF;
	/* finite = FUNCTION_CALL()(d32); */
	finite = isfinite(d32);
	printf("%d = isfinite(%Hf)\n", finite, d32);
	/*printf("%d = __finited32(%Hf)\n", __finited32(d32), d32); */


	d64  = -1.20DD;
	finite = isfinite(d64);
	/* finite = FUNCTION_CALL()(d64); */
	printf("%d = isfinite(%Df)\n", finite, d64);
	/* printf("%d = __finited64(%Df)\n", __finited64(d64), d64); */

	d64  = DEC_INFINITY;
	finite = isfinite(d64);
	/* finite = FUNCTION_CALL()(d64); */
	printf("%d = isfinite(%Df)\n", finite, d64);
	/* printf("%d = __finited64(%Df)\n", __finited64(d64), d64); */

	d64  = DEC_INFINITYDD;
	finite = isfinite(d64);
	/* finite = FUNCTION_CALL()(d64); */
	printf("%d = isfinite(%Df)\n", finite, d64);
	/* printf("%d = __finited64(%Df)\n", __finited64(d64), d64); */

	d64  = -DEC_INFINITYDD;
	finite = isfinite(d64);
	/* finite = FUNCTION_CALL()(d64); */
	printf("%d = isfinite(%Df)\n", finite, d64);
	/* printf("%d = __finited64(%Df)\n", __finited64(d64), d64); */

	d128 = -1.20DL;
	finite = isfinite(d128);
	/* finite = FUNCTION_CALL()(d128); */
	printf("%d = isfinite(%DDf)\n", finite, d128);
	/* printf("%d = __finited128(%DDf)\n", __finited128(d128), d128); */

	d128 = DEC_INFINITY;
	finite = isfinite(d128);
	/* finite = FUNCTION_CALL()(d128); */
	printf("%d = isfinite(%DDf)\n", finite, d128);
	/* printf("%d = __finited128(%DDf)\n", __finited128(d128), d128); */

	d128 = DEC_INFINITYDL;
	finite = isfinite(d128);
	/* finite = FUNCTION_CALL()(d128); */
	printf("%d = isfinite(%DDf)\n", finite, d128);
	/* printf("%d = __finited128(%DDf)\n", __finited128(d128), d128); */

	d128 = -DEC_INFINITYDL;
	finite = isfinite(d128);
	/* finite = FUNCTION_CALL()(d128); */
	printf("%d = isfinite(%DDf)\n", finite, d128);
	/* printf("%d = __finited128(%DDf)\n", __finited128(d128), d128); */


}

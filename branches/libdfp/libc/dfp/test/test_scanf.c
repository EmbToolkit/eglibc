#include <stdio.h>
#include <stdint.h>

int main() {
	_Decimal32 d32;
	_Decimal64 d64;
	_Decimal128 d128;

	char *testcases[] = { "12.04","19","19E2","-0.0001","-5","NaN", "INF"};
	int i,numCases=7;

	for(i=0; i< numCases; i++) {
		printf("in: %s\n",testcases[i]);
		sscanf(testcases[i],"%Hf", &d32);
		sscanf(testcases[i],"%Df", &d64);
		sscanf(testcases[i],"%DDf", &d128);
		printf("out: %Hf, %Df, %DDf\n",d32,d64,d128);
	}
/*	sscanf("12.04e3", "%Hf", &d32);
	sscanf("12.04", "%Df", &d64);
	sscanf("12.04", "%DDf", &d128);

	printf("out: %Hf\n",d32);
	printf("out: %Df\n",d64);
	printf("out: %DDf\n",d128); */

/*	printf("%Hf\n", d32);
	printf("%HE\n", d32); */

/*	printf("The hex value 0x%.8x%.8x = %Df in _Decimal64.\n", d64[0],
 *	d64[1], d64);  */

/*	printf("%Df\n", d64);
	printf("%DE\n", d64); */

/*	printf("The hex value 0x%.8x%.8x%.8x%.8x = %DDf in _Decimal128.\n",
 *	d128[0], d128[1], d128[2], d128[3], d128);  */
/*	printf("%DDf\n", d128); */
/*	printf("%DDE\n", d128);  */

}

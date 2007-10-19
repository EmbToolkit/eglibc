#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <stdio.h>
#include <stdint.h>

#include "test_math.h"

int main() {

	float f32;
	double f64;
	printf("\nfloat printf as float\n");
	f32 = 1.245;
	printf("'%7.2f' =(%%7.2f)%f\n",f32,f32);
	printf("'%-7.2f' = (%%-7.2f)%f\n",f32,f32);
	printf("'%.2f' = (%%.2f)%f\n",f32,f32);
	printf("'%-.2f' = (%%-.2f)%f\n",f32,f32);
	printf("'%6f' = (%%6f)%f\n",f32,f32);
	printf("'%6.f' = (%%6.f)%f\n",f32,f32);
	printf("'%.f' = (%%.f)%f\n",f32,f32);
	printf("'%f' = (%%f)%f\n",f32,f32);
	f32 = 1.245435;
	printf("'%6f' = (%%6f)%f\n",f32,f32);
	printf("'%.5f' = (%%.5f)%f\n",f32,f32);
	printf("'%-.5f' = (%%-.5f)%f\n",f32,f32);
	printf("'%-6.5f' = (%%-6.5f)%f\n",f32,f32);
	printf("'%-.4f' = (%%-.4f)%f\n",f32,f32);
	printf("'%-.5f' = (%%-.5f)%f\n",f32,f32);
	printf("'%-.6f' = (%%-.6f)%f\n",f32,f32);
	printf("'%-.7f' = (%%-.7f)%f\n",f32,f32);
	printf("'%-f' = (%%-f)%f\n",f32,f32);
	printf("'%f' = (%%f)%f\n",f32,f32);
	printf("'%10f' = (%%10f)%f\n",f32,f32);
	printf("'%-10f' = (%%-10f)%f\n",f32,f32);
	f32 = 1.245445;
	printf("'%-.4f' = (%%-.4f)%f\n",f32,f32);
	printf("'%-.5f' = (%%-.5f)%f\n",f32,f32);
	printf("'%-.6f' = (%%-.6f)%f\n",f32,f32);
	printf("'%-.6f' = (%%-.7f)%f\n",f32,f32);

	printf("\nDouble printf as float\n");
	f64 = 1.245;
	printf("'%7.2f' =(%%7.2f)%f\n",f64,f64);
	printf("'%-7.2f' = (%%-7.2f)%f\n",f64,f64);
	printf("'%.2f' = (%%.2f)%f\n",f64,f64);
	printf("'%-.2f' = (%%-.2f)%f\n",f64,f64);
	printf("'%6f' = (%%6f)%f\n",f64,f64);
	printf("'%6.f' = (%%6.f)%f\n",f64,f64);
	printf("'%.f' = (%%.f)%f\n",f64,f64);
	printf("'%f' = (%%f)%f\n",f64,f64);
	f64 = 1.245435;
	printf("'%6f' = (%%6f)%f\n",f64,f64);
	printf("'%.5f' = (%%.5f)%f\n",f64,f64);
	printf("'%-.5f' = (%%-.5f)%f\n",f64,f64);
	printf("'%-6.5f' = (%%-6.5f)%f\n",f64,f64);
	printf("'%-.4f' = (%%-.4f)%f\n",f64,f64);
	printf("'%-.5f' = (%%-.5f)%f\n",f64,f64);
	printf("'%-.6f' = (%%-.6f)%f\n",f64,f64);
	printf("'%-.7f' = (%%-.7f)%f\n",f64,f64);
	printf("'%-f' = (%%-f)%f\n",f64,f64);
	printf("'%f' = (%%f)%f\n",f64,f64);
	printf("'%10f' = (%%10f)%f\n",f64,f64);
	printf("'%-10f' = (%%-10f)%f\n",f64,f64);
	f64 = 1.245445;
	printf("'%-.4f' = (%%-.4f)%f\n",f64,f64);
	printf("'%-.5f' = (%%-.5f)%f\n",f64,f64);
	printf("'%-.6f' = (%%-.6f)%f\n",f64,f64);
	printf("'%-.6f' = (%%-.7f)%f\n",f64,f64);

	printf("\nDouble printf as double\n");
	f64 = 1.245;
	printf("'%7.2lf' =(%%7.2lf)%lf)\n",f64,f64);
	printf("'%-7.2lf' = (%%-7.2lf)%lf)\n",f64,f64);
	printf("'%.2lf' = (%%.2lf)%lf\n)",f64,f64);
	printf("'%-.2lf' = (%%-.2lf)%lf)\n",f64,f64);
	printf("'%6lf' = (%%6lf)%lf)\n",f64,f64);
	printf("'%6.lf' = (%%6.lf)%lf)\n",f64,f64);
	printf("'%.lf' = (%%.lf)%lf)\n",f64,f64);
	printf("'%lf' = (%%lf)%lf)\n",f64,f64);
	f64 = 1.245435;
	printf("'%6lf' = (%%6lf)%lf)\n",f64,f64);
	printf("'%.5lf' = (%%.5lf)%lf)\n",f64,f64);
	printf("'%-.5lf' = (%%-.5lf)%lf)\n",f64,f64);
	printf("'%-6.5lf' = (%%-6.5lf)%lf)\n",f64,f64);
	printf("'%-.4lf' = (%%-.4lf)%lf)\n",f64,f64);
	printf("'%-.5lf' = (%%-.5lf)%lf)\n",f64,f64);
	printf("'%-.6lf' = (%%-.6lf)%lf)\n",f64,f64);
	printf("'%-.7lf' = (%%-.7lf)%lf)\n",f64,f64);
	printf("'%-lf' = (%%-lf)%lf)\n",f64,f64);
	printf("'%lf' = (%%lf)%lf)\n",f64,f64);
	printf("'%10lf' = (%%10lf)%lf)\n",f64,f64);
	printf("'%-10lf' = (%%-10lf)%lf)\n",f64,f64);
	f64 = 1.245445;
	printf("'%-.4lf' = (%%-.4lf)%lf)\n",f64,f64);
	printf("'%-.5lf' = (%%-.5lf)%lf)\n",f64,f64);
	printf("'%-.6lf' = (%%-.6lf)%lf)\n",f64,f64);
	printf("'%-.6lf' = (%%-.7lf)%lf)\n",f64,f64);
	f64 = 120000000.00E10;
	printf("'%-25le'\n",f64);


        return -1;
}

/* /opt/biarch/dfp/bin/gcc -g test_signbit.c -o signbit -ldfp  */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef __STDC_WANT_DEC_FP
# define __STDC_WANT_DEC_FP__ 1
#endif
#include <math.h>
#include <float.h>
#include <fenv.h>

extern char * decoded32 (_Decimal32, char*);
extern char * decoded64 (_Decimal64, char*);
extern char * decoded128 (_Decimal128, char*);

int main() {
        _Decimal32 d32;
        _Decimal64 d64;
        _Decimal128 d128;
        char s32[32];
        char s64[64];
        char s128[128];

        float f32;
        double f64;
        long double f128;

        int i32;
        long i64;
        long long i128;

        f32 = 0.0;
        f64 = 0.0;
        f128 = 0.0;
        i32 = 0;
        i64 = 0;
        i128 = 0;

        d32 = 0.0DF;
        d64 = 0.0DD;
        d128 = 0.0DL;

        memset(s32, 0x0, 32);
        memset(s64, 0x0, 64);
        memset(s128, 0x0, 128);

        printf("%Hf.0DF: [%s]\n", d32, decoded32(d32,s32));
        printf("%Df.0DD: [%s]\n", d64, decoded64(d64,s64));
        printf("%DDf.0DL: [%s]\n", d128, decoded128(d128,s128));

        d32 = i32;
        memset(s32, 0x0, 32);
        printf("(_Decimal32)%HfDF = (int)%d: [%s]\n", d32, i32, decoded32(d32,s32));

        d32 = f32;
        memset(s32, 0x0, 32);
        printf("(_Decimal32)%Hf.0DF = (float)%f: [%s]\n", d32, f32, decoded32(d32,s32));

        d64 = i64;
        memset(s64, 0x0, 64);
        printf("(_Decimal64)%DfDD = (long)%ld: [%s]\n", d64, i64, decoded64(d64,s64));

        d64 = f64;
        memset(s64, 0x0, 64);
        printf("(_Decimal64)%Df.0DD = (double)%f: [%s]\n", d64, f64, decoded64(d64,s64));

        d128 = i128;
        memset(s128, 0x0, 128);
        printf("(_Decimal128)%DDfDL = (long long)%lld: [%s]\n", d128, i128, decoded128(d128,s128));

        d128 = f128;
        memset(s128, 0x0, 128);
        printf("(_Decimal128)%DDf.0DL = (long double)%Lf: [%s]\n", d128, f128, decoded128(d128,s128));
}

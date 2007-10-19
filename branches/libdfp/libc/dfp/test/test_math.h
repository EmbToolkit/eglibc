#ifndef __TEST_DN_MATH_H
#define __TEST_DN_MATH_H

#ifndef __STDC_WANT_DEC_FP__
# define __STDC_WANT_DEC_FP__ 1
#endif

/*#define DECNUMDIGITS 34 */

#include <stdio.h>
#include <math.h>
#include <float.h>

//Useable test case constants: DEC_NAN, DEC_INFINITY, DEC_MAX, DEC_MIN, DEC_DEN, DEC_EPSILON
//This is rather hackish... but it works (and this whole framework is supposed
//to be temporary
#define DEC_NANDF	DEC_NAN
#define DEC_NANDD	(_Decimal64)DEC_NAN
#define DEC_NANDL	(_Decimal128)DEC_NAN
#define DEC_INFINITYDF	DEC_INFINITY
#define DEC_INFINITYDD	(_Decimal64)DEC_INFINITY
#define DEC_INFINITYDL	(_Decimal128)DEC_INFINITY
#define DEC_MAXDF	DEC32_MAX
#define DEC_MAXDD	DEC64_MAX
#define DEC_MAXDL	DEC128_MAX
#define DEC_MINDF	DEC32_MIN
#define DEC_MINDD	DEC64_MIN
#define DEC_MINDL	DEC128_MIN
#define DEC_DENDF	DEC32_DEN
#define DEC_DENDD	DEC64_DEN
#define DEC_DENDL	DEC128_DEN
#define DEC_EPSILONDF	DEC32_EPSILON
#define DEC_EPSILONDD	DEC64_EPSILON
#define DEC_EPSILONDL	DEC128_EPSILON
#define trueDF		true
#define trueDD		true
#define trueDL		true
#define falseDF		false
#define falseDD		false
#define falseDL		false

//TEST_f(fabsd32,2.0DF,%Hf,-2.0DF)
//#define TEST_f(func,result,printf_t,args...)				\
//	do {								\
//		typeof(result)pres = result;				\
//		typeof(result) res = func (args);			\
//		if(res == result || (isnan(result) && isnan(res)))	\
//			printf("Success: "#printf_t" = "#func" ("#args")\n",res);\
//		else							\
//			printf("Error:   "#printf_t" = "#func" ("#args"): should be "#printf_t"\n", res, pres);\
//	} while(0)
//			/*printf("Error:   "#printf_t" = "#func" ("#args") : should be "#result"\n", res);*/


extern char * decoded32 (_Decimal32, char*);
extern char * decoded64 (_Decimal64, char*);
extern char * decoded128 (_Decimal128, char*);

typedef union {
                _Decimal32 d;
                long l[1];
        } convertd32;

typedef union {
                _Decimal64 d;
                long l[2];
        } convertd64;

typedef union {
                _Decimal128 d;
                long l[4];
        } convertd128;

#define DISP_HEXD32(got, expect) \
        do {                                                            \
                convertd32 g32, e32;                                    \
                g32.d = got;                                            \
                e32.d = expect;                                         \
		char s32[32];						\
                printf("   Result(0x%.8x) <-> expected(0x%.8x)\n", g32.l[0], e32.l[0]); \
                if (g32.d == e32.d)                                     \
                        printf("   g32.d(%Hf) == e32.d(%Hf)\n", g32.d, e32.d);                  \
                else                                                    \
                        printf("   g32.d(%Hf) != e32.d(%Hf)\n", g32.d, e32.d);                  \
		printf("   DPD for g32.d [%s]\n", decoded32(g32.d,s32));	\
		printf("   DPD for e32.d [%s]\n", decoded32(e32.d,s32));	\
                printf("\n");                                           \
        } while (0)

#define DISP_HEXD64(got, expect) \
        do {                                                            \
                convertd64 g64, e64;                                    \
                g64.d = got;                                            \
                e64.d = expect;                                         \
		char s64[64];						\
                printf("   Result(0x%.8x%.8x) <-> expected(0x%.8x%.8x)\n", g64.l[0], g64.l[1], e64.l[0], e64.l[1]);     \
                if (g64.d == e64.d)                                     \
                        printf("   g64.d(%Df) == e64.d(%Df)\n", g64.d, e64.d);                  \
                else                                                    \
                        printf("   g64.d(%Df) != e64.d(%Df)\n", g64.d, e64.d);                  \
		printf("   DPD for g64.d [%s]\n", decoded64(g64.d,s64));\
		printf("   DPD for e64.d [%s]\n", decoded64(e64.d,s64));\
                printf("\n");                                           \
        } while (0)

#define DISP_HEXD128(got, expect) \
        do {                                                            \
                convertd128 g128, e128;                                 \
                g128.d = got;                                           \
                e128.d = expect;                                        \
		char s128[128];						\
                printf("   Result(0x%.8x%.8x%.8x%.8x) <-> expected(0x%.8x%.8x%.8x%.8x)\n", g128.l[0], g128.l[1], g128.l[2], g128.l[3],e128.l[0], e128.l[1], e128.l[2], e128.l[3]);      \
                if (g128.d == e128.d)                                   \
                        printf("   g128.d(%DDf) == e128.d(%DDf)\n", g128.d, e128.d);                    \
                else                                                    \
                        printf("   g128.d(%DDf) != e128.d(%DDf)\n", g128.d, e128.d);                    \
		printf("   DPD for g128.d [%s]\n", decoded128(g128.d,s128));\
		printf("   DPD for e128.d [%s]\n", decoded128(e128.d,s128));\
                printf("\n");                                           \
        } while (0)

//TEST_f(fabsd32,2.0DF,%Hf,-2.0DF)
#define TEST_f(func,result,printf_t,args...)                            \
        do {                                                            \
                typeof(result)pres = result;                    \
                typeof(result) res = func (args);                       \
                if(res == result || (isnan(result) && isnan(res)))      \
                        printf("Success: "#printf_t" = "#func" ("#args")\n",res);\
                else {                                                  \
                        printf("Error:   "#printf_t" = "#func" ("#args"): should be "#printf_t" (" #result")\n", res, pres);\
	                if (sizeof(typeof(result)) == 16)                       \
	                        DISP_HEXD128(res, pres);                \
	                else if (sizeof(typeof(result)) == 8)                   \
	                        DISP_HEXD64(res, pres);                 \
	                else                                            \
	                        DISP_HEXD32(res, pres);                 \
		}	\
        } while(0)
                        /*printf("Error:   "#printf_t" = "#func" ("#args") : should be "#result"\n", res);*/


#define TEST_i(func,result,args...)					\
	do {								\
		long long int res = func (args);			\
		if(res != result )					\
			printf("Error:   %lld = "#func" ("#args") : should be "#result"\n", res); \
		else							\
			printf("Success: %lld = "#func" ("#args")\n",res);\
	} while(0)

#define TEST_fI(func,printf_t,result,resultI,args...)				\
	do {								\
		int the_int;						\
		typeof(result) res = func (args, &the_int);		\
		if((res == result && the_int == resultI) ||		\
				(isnan(result) && isnan(res)))		\
			printf("Success: "#printf_t","#resultI" = "#func" ("#args",&i)\n",res);\
		else							\
			printf("Error:   "#printf_t",%d = "#func" ("#args",&i) : should be "#result","#resultI"\n", res,the_int);\
	} while(0)



//Pattern is TEST_<returntype>_<# of dfp arguments>_all(func,result,arguments)
// or        TEST_<returntype>_{<f/i (for type) of arguments>_}+_all(func,result,args)
//TEST_f_all(fabs,-2.0,2.0)
#define TEST_f_1_all(func,result,arg)					\
	do {								\
		TEST_f(func##d32,result##DF,%Hf,arg##DF);		\
		TEST_f(func##d64,result##DD,%Df,arg##DD);		\
		TEST_f(func##d128,result##DL,%DDf,arg##DL);		\
	} while(0)
#define TEST_f_f_all(func,result,arg)	TEST_f_1_all(func,result,arg)


//TEST_i_all(nearbyint,0.2,0.0)
#define TEST_i_1_all(func,result,arg)			\
	do {						\
		TEST_i(func##d32,result,arg##DF);	\
		TEST_i(func##d64,result,arg##DD);	\
		TEST_i(func##d128,result,arg##DL);	\
	} while(0)
#define TEST_i_f_all(func,result,arg)	TEST_i_1_all(func,result,arg)

#define TEST_f_2_all(func,result,arg1,arg2)			\
	do {							\
		TEST_f(func##d32,result##DF,%Hf,arg1##DF, arg2##DF);	\
		TEST_f(func##d64,result##DD,%Df,arg1##DD, arg2##DD);	\
		TEST_f(func##d128,result##DL,%DDf,arg1##DL, arg2##DL);	\
	} while(0)
#define TEST_f_f_f_all(func,result,arg1,arg2)	TEST_f_2_all(func,result,arg1,arg2)

#define TEST_f_3_all(func,result,arg1,arg2,arg3)			\
	do {							\
		TEST_f(func##d32,result##DF,%Hf,arg1##DF, arg2##DF, arg3##DF);	\
		TEST_f(func##d64,result##DD,%Df,arg1##DD, arg2##DD, arg3##DD);	\
		TEST_f(func##d128,result##DL,%DDf,arg1##DL, arg2##DL, arg3##DL);\
	} while(0)

#define TEST_POLY_i_2_all(func,result,arg1,arg2)		\
	do {							\
		TEST_i(func,result,arg1##DF, arg2##DF);	\
		TEST_i(func,result,arg1##DD, arg2##DD);	\
		TEST_i(func,result,arg1##DL, arg2##DL);	\
	} while(0)


#define TEST_i_2_all(func,result,arg1,arg2)			\
	do {							\
		TEST_i(func##d32,result,arg1##DF, arg2##DF);	\
		TEST_i(func##d64,result,arg1##DD, arg2##DD);	\
		TEST_i(func##d128,result,arg1##DL, arg2##DL);	\
	} while(0)
#define TEST_i_f_f_all(func,result,arg1,arg2)	TEST_i_2_all(func,result,arg1,arg2)

#define TEST_f_i_all(func,result,arg)					\
	do {								\
		TEST_f(func##d32,result##DF,%Hf,arg);		\
		TEST_f(func##d64,result##DD,%Df,arg);		\
		TEST_f(func##d128,result##DL,%DDf,arg);	\
	} while(0)

#define TEST_f_f_i_all(func,result,arg1,arg2)			\
	do {							\
		TEST_f(func##d32,result##DF,%Hf,arg1##DF, arg2);	\
		TEST_f(func##d64,result##DD,%Df,arg1##DD, arg2);	\
		TEST_f(func##d128,result##DL,%DDf,arg1##DL, arg2);	\
	} while(0)
#endif

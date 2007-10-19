# Makefile fragment for soft-dfp.

ifeq ($(subdir),dfp)
sysdep-CFLAGS += -DWORDS_BIG_ENDIAN=1 -DLONG_DOUBLE_TYPE_SIZE=128 -DBITS_PER_UNIT=8 -Wall
libdfp-routines += \
	addsd3 adddd3 addtd3 \
	subsd3 subdd3 subtd3 \
	mulsd3 muldd3 multd3 \
	divsd3 divdd3 divtd3 \
	eqsd2 eqdd2 eqtd2 \
	nesd2 nedd2 netd2 \
	ltsd2 ltdd2 lttd2 \
	gtsd2 gtdd2 gttd2 \
	lesd2 ledd2 letd2 \
	gesd2 gedd2 getd2 \
	unordsd2 unorddd2 unordtd2 \
	extendsddd2 extendsdtd2 extendddtd2 \
	extendsfsd extendsddf extendsdtf \
	extendsfdd extenddfdd extendddtf \
	extendsftd extenddftd extendtftd \
	trunctdsd2 truncddsd2 trunctddd2 \
	truncsdsf truncdfsd trunctfsd \
	truncddsf truncdddf trunctfdd \
	trunctdsf trunctddf trunctdtf \
	fixsdsi fixddsi fixtdsi \
	fixsddi fixdddi fixtddi \
	fixunssdsi fixunsddsi fixunstdsi \
	fixunssddi fixunsdddi fixunstddi \
	floatsisd floatsidd floatsitd \
	floatdisd floatdidd floatditd \
	floatunssisd floatunssidd floatunssitd \
	floatunsdisd floatunsdidd floatunsditd \
	decpowof2 binpowof10 classify
endif

#!/bin/bash


function header {
    cat > ${1} << EOF
/* $2
   Copyright (C) 2007 IBM Corporation.

   Author(s): Pete Eberlein <eberlein@us.ibm.com>

   The Decimal Floating Point C Library is free software; you can
   redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License version 2.1.

   The Decimal Floating Point C Library is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU Lesser General Public License version 2.1 for more details.

   You should have received a copy of the GNU Lesser General Public
   License version 2.1 along with the Decimal Floating Point C Library;
   if not, write to the Free Software Foundation, Inc., 59 Temple Place,
   Suite 330, Boston, MA 02111-1307 USA.

   Please see dfp/COPYING.txt for more information.  */


EOF


}


## unaryop file op
function unaryop {

cat >> ${1} << EOF
DEC_TYPE
ACTUAL_FUNCTION_NAME (DEC_TYPE x)
{
  DEC_TYPE result;
  decNumber dn_x;
  decContext context;
  ___decContextDefault(&context, DEFAULT_CONTEXT);

  FUNC_CONVERT_TO_DN(&x, &dn_x);

  ___decNumber${2}(&result, &dn_x, &context);

  FUNC_CONVERT_FROM_DN (&dn_x, &result, &context);
  return result;
}
EOF
}


## binaryop file op
function binaryop {

cat >> ${1} << EOF
DEC_TYPE
ACTUAL_FUNCTION_NAME (DEC_TYPE x, DEC_TYPE y)
{
  DEC_TYPE result;
  decNumber dn_x, dn_y, dn_result;
  decContext context;
  ___decContextDefault(&context, DEFAULT_CONTEXT);

  FUNC_CONVERT_TO_DN(&x, &dn_x);
  FUNC_CONVERT_TO_DN(&y, &dn_y);

  ___decNumber${2}(&dn_result, &dn_x, &dn_y, &context);

  if (context.status != 0)
    {
      int ieee_flags = 0;
      if (context.status & DEC_IEEE_854_Division_by_zero)
        ieee_flags |= FE_DIVBYZERO;
      if (context.status & DEC_IEEE_854_Inexact)
        ieee_flags |= FE_INEXACT;
      if (context.status & DEC_IEEE_854_Invalid_operation)
        ieee_flags |= FE_INVALID;
      if (context.status & DEC_IEEE_854_Overflow)
        ieee_flags |= FE_OVERFLOW;
      if (context.status & DEC_IEEE_854_Underflow)
        ieee_flags |= FE_UNDERFLOW;
      if (ieee_flags != 0)
        feraiseexcept (ieee_flags);
    }

  FUNC_CONVERT_FROM_DN (&dn_result, &result, &context);
  return result;
}
EOF
}



## compareop file op
function compareop {

case $2 in
  eq) nanret=1;;
  ne) nanret=1;;
  ge) nanret=-1;;
  lt) nanret=1;;
  le) nanret=1;;
  gt) nanret=-1;;
esac


cat >> ${1} << EOF
int
ACTUAL_FUNCTION_NAME (DEC_TYPE x, DEC_TYPE y)
{
  decNumber dn_x, dn_y, result;
  decContext context;
  ___decContextDefault(&context, DEFAULT_CONTEXT);

  FUNC_CONVERT_TO_DN(&x, &dn_x);
  FUNC_CONVERT_TO_DN(&y, &dn_y);

  if(___decNumberIsNaN(&dn_x) || ___decNumberIsNaN(&dn_y))
    return ${nanret};

  ___decNumberCompare(&result, &dn_x, &dn_y, &context);
EOF

case $2 in
  eq|ne) echo "  return !___decNumberIsZero(&result);">> ${1};;
  ge|lt) echo "  return -___decNumberIsNegative(&result);">> ${1};;
  le|gt) echo "  return !___decNumberIsNegative(&result) && !___decNumberIsZero(&result);">> ${1};;
esac
echo "}" >> ${1}

}


## unord file op
function unord {

cat >> ${1} << EOF
int
ACTUAL_FUNCTION_NAME (DEC_TYPE x, DEC_TYPE y)
{
  decNumber dn_x;
  decNumber dn_y;
  decContext context;
  ___decContextDefault(&context, DEFAULT_CONTEXT);

  FUNC_CONVERT_TO_DN(&x, &dn_x);
  FUNC_CONVERT_TO_DN(&y, &dn_y);

  return (___decNumberIsNaN(&dn_x) || ___decNumberIsNaN(&dn_y));
}
EOF
}





## generate name postfix description
function generate {

  name32=${1}sd${2}
  name64=${1}dd${2}
  name128=${1}td${2}

  file32=${name32}.c
  file64=${name64}.c
  file128=${name128}.c
  desc=$3

  header $file32 "_Decimal32 $desc for soft-dfp"
  header $file64 "_Decimal64 $desc for soft-dfp"
  header $file128 "_Decimal128 $desc for soft-dfp"

    cat >> ${file32} << EOF32
#ifndef _DECIMAL_SIZE
#  include <decimal32.h>
#  define _DECIMAL_SIZE 32
#  define ACTUAL_FUNCTION_NAME __${name32}
#endif

#include <decContext.h>
#include <decNumber.h>
#include <math.h>

#define FUNCTION_NAME ${1}

#include <dfpmacro.h>
EOF32



case $1 in
  add) binaryop ${file32} Add;;
  sub) binaryop ${file32} Subtract;;
  mul) binaryop ${file32} Multiply;;
  div) binaryop ${file32} Divide;;
  eq|ne|lt|gt|le|ge) compareop ${file32} $1;;
  unord) unord ${file32};;


esac





  echo "#define _DECIMAL_SIZE 64" >> ${file64}
  echo "#define ACTUAL_FUNCTION_NAME __${name64}" >> ${file64}
  echo "#include <decimal64.h>" >> ${file64}
  echo "" >> ${file64}
  echo "#include \"${file32}\"" >> ${file64}

  echo "#define _DECIMAL_SIZE 128" >> ${file128}
  echo "#define ACTUAL_FUNCTION_NAME __${name128}" >> ${file128}
  echo "#include <decimal128.h>" >> ${file128}
  echo "" >> ${file128}
  echo "#include \"${file32}\"" >> ${file128}


}


function convert {
  op=$1
  from=$2
  to=$3
  width=
  destwidth=
  desc=$4

  case $from in
    sd) width=32; action=DECIMAL;;
    dd) width=64; action=DECIMAL;;
    td) width=128; action=DECIMAL;;
    sf) width=32; action=BINARY;;
    df) width=64; action=BINARY;;
    tf) width=128; action=BINARY;;
    si) width=32; action=INTEGER;;
    di) width=64; action=INTEGER;;
  esac


  case $to in
    sd) destwidth=32; action=${action}_TO_DECIMAL;;
    dd) destwidth=64; action=${action}_TO_DECIMAL;;
    td) destwidth=128; action=${action}_TO_DECIMAL;;
    sf) destwidth=32; action=${action}_TO_BINARY;;
    df) destwidth=64; action=${action}_TO_BINARY;;
    tf) destwidth=128; action=${action}_TO_BINARY;;
    si) destwidth=32; action=${action}_TO_INTEGER;;
    di) destwidth=64; action=${action}_TO_INTEGER;;
  esac
  
  name=${op}${from}${to}
  if [ $action == DECIMAL_TO_DECIMAL ]
  then
    name=${name}2
  fi
  file=${name}.c

echo $file
  
  header $file "${desc}"
  echo "#define ${action}" >> $file
  echo "#define SRC ${width}" >> $file
  echo "#define DEST ${destwidth}" >> $file
  echo "#define NAME ${op}" >> $file
  case ${op} in
  	fixuns|floatuns) echo "#define UNSIGNED" >> $file;;
  esac
  echo "" >> $file
  echo "#include \"convert.c\"" >> $file

}


generate add 3 addition
generate sub 3 subtraction
generate mul 3 multiplication
generate div 3 division

generate eq 2 "compare equality"
generate ne 2 "compare inequality"
generate lt 2 "compare less-than"
generate gt 2 "compare greater-than"
generate le 2 "compare less-than or equal"
generate ge 2 "compare greather-than or equal"
generate unord 2 "compare unordered"


convert extend sd dd "Handle conversion from Decimal32 to Decimal64"
convert extend sd td "Handle conversion from Decimal32 to Decimal128"
convert extend dd td "Handle conversion from Decimal64 to Decimal128"

convert extend sf sd "Handle conversion from binary float (32) to Decimal32"
convert extend sd df "Handle conversion from Decimal32 to binary double (64)"
convert extend sd tf "Handle conversion from Decimal32 to binary long double (128)"
convert extend sf dd "Handle conversion from binary float (32) to Decimal64"
convert extend df dd "Handle conversion from binary double (64) to Decimal64"
convert extend dd tf "Handle conversion from Decimal64 to binary long double (128)"
convert extend sf td "Handle conversion from binary float (32) to Decimal128"
convert extend df td "Handle conversion from binary double (64) to Decimal128"
convert extend tf td "Handle conversion from binary long double (dual 64bit) to Decimal128"

convert trunc dd sd "Handle conversion from Decimal64 to Decimal32"
convert trunc td sd "Handle conversion from Decimal128 to Decimal32"
convert trunc td dd "Handle conversion from Decimal128 to Decimal64"

convert trunc sd sf "Handle conversion from Decimal32 to binary float (32)"
convert trunc df sd "Handle conversion from binary double (64) to Decimal32"
convert trunc tf sd "Handle conversion from binary long double (128) to Decimal32"
convert trunc dd sf "Handle conversion from Decimal64 to binary float (32)"
convert trunc dd df "Handle conversion from Decimal64 to binary double (64)"
convert trunc tf dd "Handle conversion from binary long double (128) to Decimal64"
convert trunc td sf "Handle conversion from Decimal128 to binary float (32)"
convert trunc td df "Handle conversion from Decimal128 to binary double (64)"
convert trunc td tf "Handle conversion from Decimal128 to binary long double (dual 64bit)"

convert fix sd si "Handle conversion from Decimal32 to binary integer (32)"
convert fix dd si "Handle conversion from Decimal64 to binary integer (32)"
convert fix td si "Handle conversion from Decimal64 to binary integer (32)"
convert fix sd di "Handle conversion from Decimal32 to binary long (64)"
convert fix dd di "Handle conversion from Decimal64 to binary long (64)"
convert fix td di "Handle conversion from Decimal64 to binary long (64)"

convert fixuns sd si "Handle conversion from Decimal32 to binary unsigned integer (32)"
convert fixuns dd si "Handle conversion from Decimal64 to binary unsigned integer (32)"
convert fixuns td si "Handle conversion from Decimal64 to binary unsigned integer (32)"
convert fixuns sd di "Handle conversion from Decimal32 to binary unsigned long (64)"
convert fixuns dd di "Handle conversion from Decimal64 to binary unsigned long (64)"
convert fixuns td di "Handle conversion from Decimal64 to binary unsigned long (64)"

convert float si sd "Handle conversion from binary integer (32) to Decimal32"
convert float si dd "Handle conversion from binary integer (32) to Decimal64"
convert float si td "Handle conversion from binary integer (32) to Decimal128"
convert float di sd "Handle conversion from binary long (64) to Decimal32"
convert float di dd "Handle conversion from binary long (64) to Decimal64"
convert float di td "Handle conversion from binary long (64) to Decimal128"

convert floatuns si sd "Handle conversion from binary unsigned integer (32) to Decimal32"
convert floatuns si dd "Handle conversion from binary unsigned integer (32) to Decimal64"
convert floatuns si td "Handle conversion from binary unsigned integer (32) to Decimal128"
convert floatuns di sd "Handle conversion from binary unsigned long (64) to Decimal32"
convert floatuns di dd "Handle conversion from binary unsigned long (64) to Decimal64"
convert floatuns di td "Handle conversion from binary unsigned long (64) to Decimal128"


exit

makefile=Makefile
versions=Versions

echo "libdfp {" > ${versions}
echo "  GLIBC_2.5 {" >> ${versions}

echo "# Makefile fragment for soft-dfp." > ${makefile}
echo "" >> ${makefile}
echo "ifeq (\$(subdir),dfp)" >> ${makefile}
echo "sysdep-CFLAGS += -DWORDS_BIT_ENDIAN=1 -DLONG_DOUBLE_TYPE_SIZE=128 -DBITS_PER_UNIT=8" >> ${makefile}

echo "libdfp-routines +=  \\">> ${makefile}
makeline="	"


## arguments: file, description
function header {

}

## arguments: file, operation, description
function arith {

  case $1 in
    add) 

  header file



}


for ins in add sub mul div eq ne lt gt le ge unord
	do
  versionline="   ";
  for a in 32 64 128; do
    width=$a
    case $width in
	32) postfix=sd ;;
	64) postfix=dd ;;
	128) postfix=td ;;
    esac
    case $ins in
	add|sub|mul|div) 
		define=L_${ins}_${postfix}
		file=${ins}${postfix}3
		case $ins in
		add) desc="addition";;
		sub) desc="subtraction";;
		mul) desc="multiplication";;
		div) desc="division";;
		esac
		type=_Decimal${width}
		;;
	eq|ne|lt|gt|le|ge|unord) 
		define=L_${ins}_${postfix} 
		file=${ins}${postfix}2
		case $ins in
		eq) desc="compare equality";;
		ne) desc="compare inequality";;
		lt) desc="compare less-than";;
		gt) desc="compare greater-than";;
		le) desc="compare less-than or equal";;
		ge) desc="compare greater-than or equal";;
		unord) desc="compare unordered";;
		esac
		;;
	extend) case $width in
		32) define=L_sd_to_dd; width=32; file=extendsddd2
		    desc="extension to {{{_Decimal64}}}";;
		64) define=L_sd_to_td; width=32; file=extendsdtd2
		    desc="extension to {{{_Decimal128}}}";;
		128) define=L_dd_to_td; width=64; file=extendddtd2
		    desc="extension to {{{_Decimal128}}}";;
		esac
		;;
	extend2) case $width in
		32) define=L_sf_to_sd; width=32; file=extendsfsd
		    desc="extension from float";;
		64) define=L_sd_to_df; width=32; file=extendsddf
		    desc="extension to double";;
		128) define=L_sd_to_tf; width=32; file=extendsdtf
		    desc="extension to long double";;
		esac
		;;
	extend3) case $width in
		32) define=L_sf_to_dd; width=64; file=extendsfdd
		    desc="extension from float";;
		64) define=L_df_to_dd; width=64; file=extenddfdd
		    desc="extension from double";;
		128) define=L_dd_to_tf; width=64; file=extendddtf
		    desc="extension to long double";;
		esac
		;;
	extend4) case $width in
		32) define=L_sf_to_td; width=128; file=extendsftd
		    desc="extension from float";;
		64) define=L_df_to_td; width=128; file=extenddftd
		    desc="extension from double";;
		128) define=L_tf_to_td; width=128; file=extendtftd
		    desc="extension from long double";;
		esac
		;;
	
	trunc) case $width in
		32) define=L_td_to_sd; width=128; file=trunctdsd2
		    desc="truncation to {{{_Decimal32}}}";;
		64) define=L_dd_to_sd; width=64; file=truncddsd2
		    desc="truncation to {{{_Decimal32}}}";;
		128) define=L_td_to_dd; width=128; file=trunctddd2
		    desc="truncation to {{{_Decimal64}}}";;
		esac
		;;
	trunc2) case $width in
		32) define=L_sd_to_sf; width=32; file=truncsdsf
		    desc="truncation to float";;
		64) define=L_df_to_sd; width=32; file=truncdfsd
		    desc="truncation from double";;
		128) define=L_tf_to_sd; width=32; file=trunctfsd
		    desc="truncation from long double";;
		esac
		;;
	trunc3) case $width in
		32) define=L_dd_to_sf; width=64; file=truncddsf
		    desc="truncation to float";;
		64) define=L_dd_to_df; width=64; file=truncdddf
		    desc="truncation to double";;
		128) define=L_tf_to_dd; width=64; file=trunctfdd
		    desc="truncation from long double";;
		esac
		;;
	trunc4) case $width in
		32) define=L_td_to_sf; width=128; file=trunctdsf
		    desc="truncation to float";;
		64) define=L_td_to_df; width=128; file=trunctddf
		    desc="truncation to double";;
		128) define=L_td_to_tf; width=128; file=trunctdtf
		    desc="truncation to long double";;
		esac
		;;

	fixsi) define=L_${postfix}_to_si; file=fix${postfix}si; desc="conversion to signed integer";;
	fixdi) define=L_${postfix}_to_di; file=fix${postfix}di; desc="conversion to signed long";;
	fixunssi) define=L_${postfix}_to_usi; file=fixuns${postfix}si; desc="conversion to unsigned integer";;
	fixunsdi) define=L_${postfix}_to_udi; file=fixuns${postfix}di; desc="conversion to unsigned long";;
	floatsi) define=L_si_to_${postfix}; file=float${postfix}si; desc="conversion from signed integer";;
	floatdi) define=L_di_to_${postfix}; file=float${postfix}di; desc="conversion from signed long";;
	floatunssi) define=L_usi_to_${postfix}; file=floatuns${postfix}si; desc="conversion from unsigned integer";;
	floatunsdi) define=L_udi_to_${postfix}; file=floatuns${postfix}di; desc="conversion from unsigned long";;

	dfp_classify) define=L_classify_${postfix}; file=dfp_classify_${postfix}; desc="dfp classify";;
	dfp_frexp) define=L_frexp_${postfix}; file=dfp_frexp_${postfix}; desc="dfp frexp";;
	dfp_trunc) define=L_trunc_${postfix}; file=dfp_trunc_${postfix}; desc="dfp trunc";;
	dfp_classify_f) case $width in
		32) define=L_classify_sf; file=dfp_classify_sf; desc="dfp classify float";;
		64) define=L_classify_df; file=dfp_classify_df; desc="dfp classify double";;
		128) define=L_classify_tf; file=dfp_classify_tf; desc="dfp classify long double";;
		esac
		;;
    esac
    versionline="${versionline} __${file};"
#    echo ${define} ${file}.c ${width}
#    echo "||{{{__${file}}}}||<#FFCC66 (>libgcc||Power6|| ||gcc/gcc/config/rs6000/dfp.md||{{{_Decimal${width}}}} ${desc}||"
#    echo "||{{{__${file}}}}||<#99CC99 (>libdfp||generic||missing||libc/dfp/sysdeps/soft-dfp/${file}.c||{{{_Decimal${width}}}} ${desc}||"
#    echo "||{{{__${file}}}}||<#99CC99 (>libdfp||Power6||completed||libc/dfp/sysdeps/powerpc/powerpc32/power6/fpu/${file}.S||{{{_Decimal${width}}}} ${desc}||"
    echo "||{{{__${file}}}}||<#FFCC66 (>complete||<#99CC99 (>complete||<#99CC99 (>complete|| ||{{{_Decimal${width}}}} ${desc}||"

    makeline="${makeline} ${file}"

    cat > ${file}.c << EOF
/* _Decimal${width} $desc for soft-dfp
   Copyright (C) 2007 IBM Corporation.

   Author(s): Pete Eberlein <eberlein@us.ibm.com>

   The Decimal Floating Point C Library is free software; you can
   redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License version 2.1.

   The Decimal Floating Point C Library is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU Lesser General Public License version 2.1 for more details.

   You should have received a copy of the GNU Lesser General Public
   License version 2.1 along with the Decimal Floating Point C Library;
   if not, write to the Free Software Foundation, Inc., 59 Temple Place,
   Suite 330, Boston, MA 02111-1307 USA.

   Please see dfp/COPYING.txt for more information.  */


EOF

  if [ ${width} == 32 ]; then
    file32=${file}.c
    cat > ${file32} << EOF32
#ifndef _DECIMAL_SIZE
#  include <decimal32.h>
#  define _DECIMAL_SIZE 32
#endif
#include <errno.h>


${type} ${file} (

EOF32

  elif [ ${width} == 64 ]; then
     echo "#define _DECIMAL_SIZE 64" >> ${file}.c
     echo "#include <decimal64.h>" >> ${file}.c
     echo "" >> ${file}.c
     echo "#include \"${file32}\"" >> ${file}.c

  elif [ ${width} == 128 ]; then
     echo "#define _DECIMAL_SIZE 128" >> ${file}.c
     echo "#include <decimal128.h>" >> ${file}.c
     echo "" >> ${file}.c
     echo "#include \"${file32}\"" >> ${file}.c
  fi




  done
  echo "${versionline}" >> ${versions}
  echo "${makeline} \\" >> ${makefile}
  makeline="	"

done

echo "  }" >> ${versions}
echo "}" >> ${versions}

echo "endif" >> ${makefile}

exit 

cat > ${file}.c << EOF
/* Declare arithmetic operations using 32-bit decimal types
   Copyright (C) 2006 IBM Corporation.

   Author(s): Pete Eberlein <eberlein@us.ibm.com>

   The Decimal Floating Point C Library is free software; you can
   redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License version 2.1.

   The Decimal Floating Point C Library is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU Lesser General Public License version 2.1 for more details.

   You should have received a copy of the GNU Lesser General Public
   License version 2.1 along with the Decimal Floating Point C Library;
   if not, write to the Free Software Foundation, Inc., 59 Temple Place,
   Suite 330, Boston, MA 02111-1307 USA.

   Please see dfp/COPYING.txt for more information.  */


#define WIDTH 32

#define L_addsub_sd
#define L_mul_sd
#define L_div_sd

#define L_eq_sd
#define L_ne_sd
#define L_lt_sd
#define L_gt_sd
#define L_le_sd
#define L_ge_sd

#define DFP_EXCEPTIONS_ENABLED 1
#define DFP_HANDLE_EXCEPTIONS feraiseexcept

EOF



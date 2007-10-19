#include <stdio.h>
void
f (long r3, long r4, long r5, long r6,
   long r7, long r8, long r9, long r10,
   _Decimal64 f1, _Decimal64 f2, _Decimal64 f3, _Decimal64 f4,
   _Decimal64 f5, _Decimal64 f6, _Decimal64 f7, _Decimal64 f8,
   long onstack, ...)
{
  __builtin_va_list ap;
  _Decimal128 ld;

  __builtin_va_start (ap, onstack);

  ld = __builtin_va_arg (ap, _Decimal128);
  if (ld != 1.23DL) {
    printf("%Hf,%Df,%DDf\n", ld,ld,ld);
    __builtin_abort ();
  }

  __builtin_va_end (ap);
}

int
main (void)
{
  f (1, 2, 3, 4, 5, 6, 7, 8,
     0, 0, 0, 0, 0, 0, 0, 0,
     99, 1.23DL);
  return 0;
}

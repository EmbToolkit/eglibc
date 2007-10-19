void
f (long r3, long r4, long r5, long r6,
   long r7, long r8, long r9, long r10,
   double f1, double f2, double f3, double f4,
   double f5, double f6, double f7, double f8,
   long onstack, ...)
{
  __builtin_va_list ap;
  long double ld;

  __builtin_va_start (ap, onstack);

  ld = __builtin_va_arg (ap, long double);
  if (ld != 1.23L)
    __builtin_abort ();

  __builtin_va_end (ap);
}

int
main (void)
{
  f (1, 2, 3, 4, 5, 6, 7, 8,
     0, 0, 0, 0, 0, 0, 0, 0,
     99, 1.23L);
  return 0;
}

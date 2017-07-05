#include "randlib.h"
#include<immintrin.h>

//initialize the hardware_rand64
extern unsigned long long hardware_rand64 (void)
{
  unsigned long long int number;
  while (! _rdrand64_step (&number))
    continue;
  return number;
}

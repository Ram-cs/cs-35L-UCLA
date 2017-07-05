#include"randcpuid.h"
#include<cpuid.h>

//current CPU discription
static struct cpuid { unsigned eax, ebx, ecx, edx; };

//return CPU information  See <http://wiki.osdev.org/CPUID>.
static struct cpuid
cpuid (unsigned int leaf, unsigned int subleaf)
{
  struct cpuid result;
  asm ("cpuid"
       : "=a" (result.eax), "=b" (result.ebx),
	 "=c" (result.ecx), "=d" (result.edx)
       : "a" (leaf), "c" (subleaf));
  return result;
}
extern _Bool rdrand_supported (void)
{
  struct cpuid extended = cpuid (1, 0);
  return (extended.ecx & bit_RDRND) != 0;
}

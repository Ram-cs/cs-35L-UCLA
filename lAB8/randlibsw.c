#include "randlib.h"
#include<stdio.h>
#include<stdlib.h>

//implimentaion of software

//input sream contain reandom bytes
static FILE *urandstream;

//software_rand64_init initialization
__attribute__ ((constructor)) static void software_rand64_init (void)
{
  urandstream = fopen ("/dev/urandom", "r");
  if (! urandstream)
    abort ();
}

//using software operator return random value
extern unsigned long long software_rand64 (void)
{
  unsigned long long int temp;
  if (fread (&temp, sizeof temp, 1, urandstream) != 1)
    abort ();
  return temp;
}

//finalizing the softwae_rand64_fini implimentaion
__attribute__ ((destructor)) static void software_rand64_fini (void)
{
  fclose (urandstream);
}

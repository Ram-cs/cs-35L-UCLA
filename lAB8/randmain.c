#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include "randcpuid.h"
#include <stdbool.h>


static bool
byteWrite (unsigned long long x, int nbytes)
{
    int ndigits = nbytes * 2;
    do
    {
        if (putchar ("0123456789abcdef"[x & 0xf]) < 0)
            return false;
        x >>= 4;
        ndigits--;
    }
    while (0 < ndigits);
    
    return 0 <= putchar ('\n');
}

/* output N bytes of random data */
int main (int argc, char **argv)
{
    /* check for the arguments */
    bool isValid = false;
    long long nbytes;
    if (argc == 2)
    {
        char *endptr;
        errno = 0;
        nbytes = strtoll (argv[1], &endptr, 10);
        if (errno)
            perror (argv[1]);
        else
            isValid = !*endptr && 0 <= nbytes;
    }
    if (!isValid)
    {
        fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
        return 1;
    }
    
    /* no work to do, no worries which library to use  */
    if (nbytes == 0)
        return 0;
    
    /* arrange to use library  */
    void *libry;
    unsigned long long (*rand64) (void);
    int HW = 0;
    
    if (rdrand_supported ())
    {
        libry = dlopen("./randlibhw.so", RTLD_NOW);
        if (libry == NULL)
        {
            printf("Can't open ./randlibhw.so : %s\n", dlerror());
            exit(1);
        }
        
        rand64 = dlsym(libry, "hardware_rand64");
        
        if (dlerror())
        {
            printf("Can't locate hardware_rand64: %s\n", dlerror());
            exit(1);
        }
        HW = 1;
    }
    else
    {
        libry = dlopen("./randlibsw.so", RTLD_NOW);
        if (libry == NULL)
        {
            printf("Can't open ./randlibsw.so: %s\n", dlerror());
            exit(1);
        }
        
        rand64 = dlsym(libry, "software_rand64");
        
        if (dlerror())
        {
            printf("Can't locate software_rand64: %s\n", dlerror());
            exit(1);
        }
    }
    
    if (HW == 1)
    {
        printf("HW\n");
    }
    else
    {
        printf("SW\n");
    }
    
    int wordsize = sizeof rand64 ();
    int output_errno = 0;
    
    do
    {
        unsigned long long x = rand64 ();
        int outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (!byteWrite (x, outbytes))
        {
            output_errno = errno;
            break;
        }
        nbytes -= outbytes;
    }
    while (0 < nbytes);
    
    if (fclose (stdout) != 0)
        output_errno = errno;
    
    if (output_errno)
    {
        errno = output_errno;
        perror ("output");
        return 1;
    }
    
    dlclose(libry);
    return 0;
}



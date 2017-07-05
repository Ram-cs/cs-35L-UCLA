Ram Yadav 
Paul Eggert

I downloaded the ray tracer code from the Brian Allen’s SRT implementation

after that i ran the command
make clean check, i got following output
rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
main.c:250:31: warning: 'gamma' is deprecated: first deprecated in macOS 10.9
      [-Wdeprecated-declarations]
            scaled_color[0] = gamma( pixel_color[0] ) * max_color;
                              ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include/math.h:759:15: note: 
      'gamma' has been explicitly marked deprecated here
extern double gamma(double) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, _...
              ^
main.c:251:31: warning: 'gamma' is deprecated: first deprecated in macOS 10.9
      [-Wdeprecated-declarations]
            scaled_color[1] = gamma( pixel_color[1] ) * max_color;
                              ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include/math.h:759:15: note: 
      'gamma' has been explicitly marked deprecated here
extern double gamma(double) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, _...
              ^
main.c:252:31: warning: 'gamma' is deprecated: first deprecated in macOS 10.9
      [-Wdeprecated-declarations]
            scaled_color[2] = gamma( pixel_color[2] ) * max_color;
                              ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk/usr/include/math.h:759:15: note: 
      'gamma' has been explicitly marked deprecated here
extern double gamma(double) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, _...
              ^
3 warnings generated.
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m29.348s
user	0m28.831s
sys	0m0.183s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp
./srt: Multithreading is not supported yet.

real	0m0.020s
user	0m0.001s
sys	0m0.002s
make: *** [2-test.ppm] Error 1

I got error, i guessed it was because of the parallelization wasn’t implemented

So, i used pthread_create and pthread_join to implement parallelization
. Doing this, i will have pointer of p_threads that helps me for the 
iteration and passing an arguments, and for other second argument 
i passed NULL

the four loops inside the main function are parallel, moved these loops
into separate file and called threads to be parallelize. By doing, returns
void* in order to make pthread_create work.

Under the main, created the idForThread, and Thread. Doing so helped me
cast the integer pointers and dereference them in the function.
 
I passed the threads different starting with indices from 0 to -1, and 
combined later that would iterate through all the elements, resulted 
nested loops go through all value of px and iterating by adding nthreads.

I changed the array to store float value of scaled color of [width][height][3];
I also made global variables for easyness as not to have to call the function
every time . Then in the main function print everything. For the array i used
malloc.  

rm -f *.o *.ppm *.tmp srt srt.tgz
3 warnings generated.
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm -lpthread
time ./srt 1-test.ppm >1-test.ppm.tmp && mv 1-test.ppm.tmp 1-test.ppm

real	0m28.434s
user	0m28.320s
sys	0m0.046s
time ./srt 2-test.ppm >2-test.ppm.tmp && mv 2-test.ppm.tmp 2-test.ppm

real	0m14.086s
user	0m27.912s
sys	0m0.025s
time ./srt 4-test.ppm >4-test.ppm.tmp && mv 4-test.ppm.tmp 4-test.ppm

real	0m13.366s
user	0m49.025s
sys	0m0.123s
time ./srt 8-test.ppm >8-test.ppm.tmp && mv 8-test.ppm.tmp 8-test.ppm

real	0m16.968s
user	0m49.473s
sys	0m0.401s
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
	  diff -u 1-test.ppm $file || exit; \
	done
I noticed that there were significant improvement in timing in execution
and imaged produced are the same. The timing improve because of the number of
thread increased. 

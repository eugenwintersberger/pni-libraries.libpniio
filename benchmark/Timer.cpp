
extern "C"{
#include<time.h>
#include<sys/time.h>
}

#include "Timer.hpp"


double Timer::time()
{
    struct timeval time;
    gettimeofday(&time,NULL);

    double sec = time.tv_sec;
    double usec = time.tv_usec;

    return sec+1.e-6*usec;
}

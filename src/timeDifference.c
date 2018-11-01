#include "timeDifference.h"
#include "time.h"
#include "globalHeader.h"
#include "stdio.h"

double _getVariableDt();


double getDt(){
    #ifdef CONSTANT_TIMER
	 return SLEEP_TIME_S;

    #elif  defined(VARIABLE_TIMER)

    return _getVariableDt();
    #else 

    #endif // TIMER TYPE


}

double _getVariableDt(){
    static long old_ns; 
    long new_ns; 
    struct timespec currentTime;
     clock_gettime(CLOCK_REALTIME, &currentTime);
	 new_ns = currentTime.tv_nsec; 	
	 printf("dt: %f %ld, %ld \n",(new_ns - old_ns)/(1000*1000*1000.0), new_ns,  old_ns);
	 double out = (new_ns - old_ns)/(1000*1000*1000.0);
	 old_ns = new_ns;
	 return out; 
}
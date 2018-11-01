#include "timeDifference.h"
#include "time.h"
#include "globalHeader.h"
#include "stdio.h"

double _getVariableDt();
double _lowPassedDt();

double getDt(){
    #ifdef CONSTANT_TIMER
	 return SLEEP_TIME_S;

    #elif  defined(VARIABLE_TIMER)

    return _getVariableDt();

    #elif  defined(LOW_PASS_TIMER)

    return  _lowPassedDt(); 
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


double _lowPassedDt(){
    static double out = SLEEP_TIME_S; 
    double change = _getVariableDt(); 
    const double tau = 0.1; // How quickly the estimate changes
    out = (1-tau)*tau  + tau*change; 

}
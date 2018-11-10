#include "timeDifference.h"
//#include "time.h"
#include "globalHeader.h"
#include "stdio.h"
#include "sharedVariables.h"
#include "stdlib.h"
double _getVariableDt();

double _lowPassDt();


void timeDifference_wait_us(int sleepTime_us){

    //int clock_nanosleep(clockid_t clock_id, int flags, const struct timespec* request, struct timespec* remain)
    //struct timespec dt; 

    //clock_nanosleep( CLOCK_MONOTONIC, 0, )
    usleep(sleepTime_us); 

}
void timeDifference_init(){
    _getVariableDt(); 
}
double timeDifference_getDt(){
 

   //return CONTROLLER_PERIOD_S;
    //return _getVariableDt(); 
    return _lowPassDt(); 

}

double _getVariableDt(){
    static long old_ns; 
    static double oldOut =0; // If out is unreasonable (timewarp)
    long new_ns; 
    struct timespec currentTime;
     clock_gettime(CLOCK_MONOTONIC, &currentTime);
	 new_ns = currentTime.tv_nsec; 	
	 double out = (new_ns - old_ns)/(1000*1000*1000.0);
	 old_ns = new_ns;


     if( out < 0.0000001 ){ // The clock suffers som timewarps, even though we have set timer to MONOTONIC
        out = oldOut; // Intrapolate becaouse of bad value
     } // We do not protect ourselves from positive timewarps 

     oldOut = out;
	 return out; 
}


double _lowPassDt(){
    static readCounter =0; 
    static double out = INITIAL_DT_ESTIMATE; 
    const double tau = 0.06; 
    double change; 
    


    change = _getVariableDt(); 


    out = (1.0-tau)*out + tau*change; 
    //printf("dt: %f \n", out);
    return out; 


}

#include "timeDifference.h"
#include "time.h"
#include "globalHeader.h"
#include "stdio.h"

double _getVariableDt();

double _lowPassDt();



double getDt(){
 

   return SLEEP_TIME_S;
    //return _lowPassDt(); 

}

double _getVariableDt(){
    static long old_ns; 
    long new_ns; 
    struct timespec currentTime;
     clock_gettime(CLOCK_MONOTONIC, &currentTime);
	 new_ns = currentTime.tv_nsec; 	
	 //printf("dt: %f %ld, %ld \n",(new_ns - old_ns)/(1000*1000*1000.0), new_ns,  old_ns);
	 double out = (new_ns - old_ns)/(1000*1000*1000.0);
	 old_ns = new_ns;
	 return out; 
}


double _lowPassDt(){
    static readCounter =0; 
    static double out = SLEEP_TIME_S; 
    const double tau = 0.006; 
    double change = out;
    
    if( ++readCounter == 5){
         change = _getVariableDt() /10;
         readCounter =0;  
    }

    out = (1-tau)*out + tau*change; 
    return out; 


}

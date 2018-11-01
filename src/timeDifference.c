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
    const double tau = 0.06; 
    double change = out;
    

    
    static int counter = 20; 
    if( counter -- ==0){
        counter =20; 
        change = _getVariableDt()/20; 
        printf("change: %f\n", change);
        if(change <= 0){
            change = out; 
        }
        
    }
    else{
        change = out; 
    }

    out = (1.0-tau)*out + tau*change; 
    printf("dt: %f \n", out);
    return out; 


}

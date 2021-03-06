#include "timeDifference.h"
#include "stdio.h"
#include "sharedVariables.h"

// API-functions are writen to as:
// timeDifference_<functionName>_<unit of measurement>()


// Internal functions
double _getVariableDt_s();
double _lowPassDt_s();


void timeDifference_wait_us(int sleepTime_us){
    	usleep(sleepTime_us); 
}
void timeDifference_init(){
    	_getVariableDt_s(); 
}
double timeDifference_getDt_s(){
	printf("FUN %f\n", INITIAL_DT_ESTIMATE_S);
    	return (double)INITIAL_DT_ESTIMATE_S;
   	//return _getVariableDt_s(); 
    	//return _lowPassDt_s(); 
}

double _getVariableDt_s(){
    	static long old_ns; 
    	static double oldOut =0; // If out is unreasonable (timewarp)
    	long new_ns; 
    	struct timespec currentTime;
    	clock_gettime(CLOCK_MONOTONIC, &currentTime);
	new_ns = currentTime.tv_nsec; 	
	double out = (new_ns - old_ns)/(1000*1000*1000.0);
	old_ns = new_ns;


     	if( out < 0.0000001 ){ // The clock suffers som timewarps, even though we have set timer to MONOTONIC
        	out = oldOut; // Intrapolate because of a bad value
	} // We do not protect ourselves from positive timewarps 
	oldOut = out;
	return out; 
}



// Estimate average period if the time-period is noisy
double _lowPassDt_s(){
	static readCounter =0; 
	static double out = INITIAL_DT_ESTIMATE_S; 
    	const double tau = 0.06; 
	double change; 
    


	change = _getVariableDt_s(); 


    	out = (1.0-tau)*out + tau*change;
    	return out; 
}

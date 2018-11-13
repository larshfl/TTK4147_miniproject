
#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H





// Global variables
#include "../miniproject-files/network/udp.h"


extern UDPConn* CONN; 
extern float REF;
extern float Y; 


// Global constants 

#define true	(1)
#define false   (0)
#define CONTROLLER_SLEEP_PERIOD_S (0.001)
#define INITIAL_DT_ESTIMATE_S (CONTROLLER_SLEEP_PERIOD_S + 0.003) // Measured from low-pass filter
#define IP_ADDR "10.100.23.176"
#define S_TO_US 1000*1000








#endif   /* SHARED_VARIABLES_H*/


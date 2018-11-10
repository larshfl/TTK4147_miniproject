
#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H





// Global variables
#include "../miniproject-files/network/udp.h"


extern UDPConn* CONN; 
extern double REF;
extern double Y; 


// Global constants 

#define true	(1)
#define false   (0)
#define CONTROLLER_SLEEP_PERIOD_S (0.001)
#define INITIAL_DT_ESTIMATE (CONTROLLER_SLEEP_PERIOD_S + 0.003) // Measured 
#define IP_ADDR "10.100.23.244"
#define S_TO_US 1000*1000



// Global definitions





#define EPSILON (0)
#define inEps(A) ( ! ( (A>EPSILON) || (A< -EPSILON)) )









#endif 
/* SHARED_VARIABLES_H*/


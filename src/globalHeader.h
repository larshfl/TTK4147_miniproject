
#ifndef GLOBAL_HEADER_H
#define GLOBAL_HEADER_H


double getDt();






// Usefull defines
#define true	(1)
#define false   (0)
#define SLEEP_TIME_S (0.001)
#define IP_ADDR "10.100.23.253"
#define S_TO_US 1000*1000

// Floating point comparison
#define EPSILON (0)
#define inEps(A) ( ! ( (A>EPSILON) || (A< -EPSILON)) )


//#define VARIABLE_TIMER

#endif //GLOBAL_HEADER_H

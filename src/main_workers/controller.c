

#include "sharedVariables.h"
#include "stdio.h"

// To delete 




#include "../miniproject-files/network/udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <semaphore.h>
#include "timeDifference.h"
#include "globalHeader.h"




//const double Kp = 8;
//const double Ki = 800;

const double Kp = 5;
const double Ki = 1000;

const double Kd = 0.01;

//
double _calculateU(double dt, double error); 

void* controller_main(void* args){

    int i; 
	char send_buff[100] = "sent";
	int buflen = 100;
	memcpy( send_buff, "SET:", sizeof(char)*4);
    long old_ns, new_ns; 


	// Remember that the DHCP can change the IP of the computers ( run setup.sh first )





	


	//double y;
	double error; 
	double u; 



		
	while(1) {
    


	 double dt = timeDifference_getDt();
	 printf("dt : %f\n",  dt); 
//	 printf("dt: %f \n", dt);
	 error = REF -Y; 
	 u = _calculateU( dt,  error);



	

	// Network stuff
	snprintf(send_buff+4, 100, "%lf",u); 
    
    udpconn_send(CONN, send_buff);

    printf("C: %s\n", send_buff);

    timeDifference_wait_us((int)(CONTROLLER_SLEEP_PERIOD_S*S_TO_US)); 
    udpconn_send(CONN, "GET");

    }
     

	return NULL;
} 



inline double limitedD(double dt, double error){
	static double x =0.1; 
	const double tau= 1;
	x = x + dt*( -x-error)/tau; 
	double y = error -x; 
	return y; 
}

double _calculateU(double dt, double error){
        static double prev_error =0.0; 
        static double I =0.0; 
        
        double P = error;		
		I += (error*dt);
		const double beta =1; 
		const double tau = 1; 
		//double D = (error - prev_error)*( beta*tau/(dt+tau));
		double D = limitedD(dt, error);
		printf("ud: %f \n", D);
		// printf("P: %lf, I:  %lf, D:  %lf\n", P,I,D);
		prev_error = error;	



		double u = Kp*error + Ki*I + Kd*D;

        return u; 
}


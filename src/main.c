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


/*

- tune regulator?
- skrive rapport
- prioritet eller kernel moduler?


*/

// Regulator parameters

	const double Kp = 0.5;
	const double Ki = 1600;

	const double Kd = 0.001;
double controll(double dt, double error);

int ref;
int* signal_shared;

double Y; 
double SIG; 
pthread_mutex_t Y_LOCK; 
sem_t SIG_SEM; 


void* receive(void* args){
	char rcv_buff[100] = "Thread \n";
	int buflen = 100;
	
	UDPConn* conn = udpconn_new(IP_ADDR, 9999);
    
	printf("START_DATA\n"); 
	udpconn_send(conn, "START");
	udpconn_send(conn, "GET");
	printf("Q\n");

	
	while(1){
        udpconn_receive(conn,rcv_buff,buflen);
        if(rcv_buff[0] == 'G'){
            // Reg 
            pthread_mutex_lock(&Y_LOCK);
            Y= atof(rcv_buff + 8);
            pthread_mutex_unlock(&Y_LOCK); 
            
        	udpconn_send(conn, "GET");
        
        }
        else{
            // Signal 
            udpconn_send(conn, "SIGNAL_ACK");
            //sem_post(&SIG_SEM); 
        }

        
	}

	return NULL;
} 
void* controller(void* args){

    int i; 
	char send_buff[100] = "sent";
	int buflen = 100;
	memcpy( send_buff, "SET:", sizeof(char)*4);
	struct timespec currentTime;
    long old_ns, new_ns; 
    clock_gettime(CLOCK_REALTIME, &currentTime);
    old_ns =  currentTime.tv_nsec; 
	// Remember that the DHCP can change the IP of the computers
	UDPConn* conn = udpconn_new(IP_ADDR, 9999);




	


	double y;
	double u, error; 



		
	while(1) {
    


	 double dt = getDt();
	 printf("dt: %f \n", dt);
	 error = ref -Y; 
	 u = controll( dt,  error);
	 
	 snprintf(send_buff+4, 100, "%lf",u); 
     udpconn_send(conn, send_buff);
	 usleep((int)(SLEEP_TIME_S*S_TO_US)); 
		



}


	



}


     

	return NULL;
} 



double controll(double dt, double error){
        static double prev_error =0.0; 
        static double I =0.0; 
        
        double P = error;		
		I += (error*dt);
		double D = (error - prev_error)/dt;
		
		// printf("P: %lf, I:  %lf, D:  %lf\n", P,I,D);
		prev_error = error;	



		double u = Kp*error + Ki*I + Kd*D;

        return u; 
}



void* signal(void* args){
    UDPConn* conn = udpconn_new(IP_ADDR, 9999);
    while(1){
        sem_wait(&SIG_SEM); 
        udpconn_send(conn, "SIGNAL_ACK");
       // printf("GOT IT\n");
    }
	return NULL;
} 






int main(){



    pthread_mutex_init(&Y_LOCK, NULL); 
    sem_init(&SIG_SEM, true, 0);

    
    pthread_t threadHandles[3];
    pthread_create(&threadHandles[0], NULL, receive, NULL);
    pthread_create(&threadHandles[1], NULL, controller, NULL);
   // pthread_create(&threadHandles[2], NULL, signal, NULL);
    
    ref = 1;
    usleep(1000*1000);
    ref = 0;
    usleep(1000*1000);
    UDPConn* conn = udpconn_new(IP_ADDR, 9999);
    udpconn_send(conn, "SIGNAL_ACK");
    udpconn_send(conn, "STOP");
    
     
   

	

	return 0;

}


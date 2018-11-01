#include "../miniproject-files/network/udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <semaphore.h>

#define true	(1)
#define false   (0)
#define SLEEP_TIME_S (0.001)
#define IP_ADDR "10.100.23.244"
#define S_TO_US 1000*1000



/*

- tune regulator?
- skrive rapport
- prioritet eller kernel moduler?


*/



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
            sem_post(&SIG_SEM); 
        }

        
	}

	return NULL;
} 

void* controller(void* args){

    int i; 
	char send_buff[100] = "sent";
	int buflen = 100;
	memcpy( send_buff, "SET:", sizeof(char)*4);


	// Remember that the DHCP can change the IP of the computers
	UDPConn* conn = udpconn_new(IP_ADDR, 9999);




	

	double I = 0;
	double Kp = 0.1;
	double Ki = 1600;
	double Kd = 0;
	double y,P,dt, oldT, y_old = 0;
	double u, error, prev_error, D; 



		
	while(1) {

		//clock_gettime(CLOCK_REALTIME, &time);


        y = Y; 
        printf("%lf\n", y); 
	
		dt = SLEEP_TIME_S; 
		
       // y form other
		error = ref - y;
		P = error;		
		I += error*dt;
		D = (error - prev_error)/dt;
		prev_error = error;	



		u = Kp*error + Ki*I + Kd*D;
		// printf("P: %f I: %f D: %f u: %f \n", P, I, D, u);


		snprintf(send_buff+4, 100, "%lf",u); 
		udpconn_send(conn, send_buff);
		usleep((int)(SLEEP_TIME_S*S_TO_US)); 
		



	}


	return NULL;
} 




void* signal(void* args){
    UDPConn* conn = udpconn_new(IP_ADDR, 9999);
    while(1){
        sem_wait(&SIG_SEM); 
        udpconn_send(conn, "SIGNAL_ACK");
        printf("GOT IT\n");
    }
	return NULL;
} 






int main(){



    pthread_mutex_init(&Y_LOCK, NULL); 
    sem_init(&SIG_SEM, true, 0);

    
    pthread_t threadHandles[3];
    pthread_create(&threadHandles[0], NULL, receive, NULL);
    pthread_create(&threadHandles[1], NULL, controller, NULL);
    pthread_create(&threadHandles[2], NULL, signal, NULL);
    
    ref = 1;
    usleep(1000*1000);
    ref = 0;
    usleep(1000*1000);
    UDPConn* conn = udpconn_new(IP_ADDR, 9999);
    udpconn_send(conn, "STOP");
    
     
   

	

	return 0;

}








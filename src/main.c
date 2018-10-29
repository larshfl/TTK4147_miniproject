#include "../miniproject-files/network/udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>


#define true	(1)
#define false   (0)
#define SLEEP_TIME_S (0.001)
#define IP_ADDR "10.24.35.107"
long str2long(char*s){
	long out =0; 
	int i;

	for(i=0; s[i] != '.' && s[i] != '\0'; ++i){
		printf("%i\n", (int)s[i]); 
		out*= 10; 
		out+= s[i]- '0'; 
	} 
	return out;
}


int l2s(long N, char* s){
	if(N<0){
		s[0] ='-';
		l2s(-N, s+1);
	}
	int base = N%10; 
	long rest =  N/10; 
	int ind; 
	if(rest != 0){
		ind = l2s(rest, s); 
	}
	else{
			ind =0; 
	}
	s[ind] = base+'0' ;
	return ind+1; 
}





void* fn(void* args){
	char rcv_buff[100] = "Thread \n";
	int buflen = 100;
	
	UDPConn* conn = udpconn_new("10.100.23.253", 9999);

	while(1){
		printf("a \n");
		//udpconn_receive(conn, rcv_buff,100);
		//printf(rcv_buff);
		printf("a \n");
	}

	return NULL;
} 



int main(){


	int i; 
	char send_buff[100] = "sent";
	int buflen = 100;
	memcpy( send_buff, "SET:", sizeof(char)*4);
	// send_buff[0] = "sent";	

	// Remember that the DHCP can change the IP of the computers
	UDPConn* conn = udpconn_new("10.100.23.253", 9999);
	char rcv_buff[100];

	for(i = 0; i < 100; i++){
		printf("\n");
	}
	printf("START_DATA\n"); 
	udpconn_send(conn, "START");
	udpconn_send(conn, "GET");
	printf("Q\n");



	udpconn_receive(conn,rcv_buff,buflen);
	printf("Received\n"); 

	
	double ref = 1;
	double I = 0;
	double Kp = 1;
	double Ki = 1600;
	double Kd = 0;
	double y,P,dt, oldT, y_old = 0;
	double u, error, prev_error, D; 


	struct timespec starttime, time;
	clock_gettime(CLOCK_REALTIME, &starttime);
		
	while(1) {

		clock_gettime(CLOCK_REALTIME, &time);
		if(time.tv_sec-starttime.tv_sec > 1){
			ref = 0;
    }

		udpconn_send(conn, "GET");
	
		dt = SLEEP_TIME_S; 
		udpconn_receive(conn,rcv_buff,buflen);
		
		y = atof(rcv_buff + 8);
		error = ref - y;
		P = error;		
		I += error*dt;
		D = (error - prev_error)/dt;
		prev_error = error;	



/*
		P = ref - y;
		I+= (ref - y) * dt;
		u = P*Kp + (I*Ki) + (y - y_old)/SLEEP_TIME_S*Kd;
		y_old = y; 
*/
		u = Kp*error + Ki*I + Kd*D;
		// printf("P: %f I: %f D: %f u: %f \n", P, I, D, u);


		snprintf(send_buff+4, 100, "%lf",u); 
		udpconn_send(conn, send_buff);
		usleep((int)(SLEEP_TIME_S*1000*1000*1)); 
		

		if(time.tv_sec-starttime.tv_sec > 2){
				udpconn_send(conn, "STOP");
				break;
		}
			


	}

	printf("smulation finished \n");

	return 0;

}








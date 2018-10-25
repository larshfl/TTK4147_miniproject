#include "../miniproject-files/network/udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include "string.h"

#define true	(1)
#define false   (0)

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

	

	char send_buff[100] = "sent";
	int buflen = 100;
	memcpy( send_buff, "sent", sizeof(char)*6);
	// send_buff[0] = "sent";	

	UDPConn* conn = udpconn_new("10.100.23.253", 9999);
	char rcv_buff[100];;

	

	udpconn_send(conn, "START");
	udpconn_send(conn, "GET");
	printf("Q\n");
	udpconn_receive(conn,rcv_buff,buflen);

	double ref = 0;
	double I = 0;
	
	double Kp = 10;
	double Ki = 800;

	double y,P,dt, oldT;
	double u; 
	 
	
	
		
	while(1) {

		

		udpconn_send(conn, "GET");
		usleep(10); 
		dt = 10; 
		udpconn_receive(conn,rcv_buff,buflen);
		printf("main got %s \n", rcv_buff);
		
		y = str2long(rcv_buff+8);
		printf("rcv buff: %s \n", rcv_buff);  
		P = y;
		I+= (y*dt)/1000000;
		u = P*Kp + (I*Ki);
		l2s((-u), send_buff);

		udpconn_send(conn, send_buff);
		printf("y: %i\n", (int)y); 
		printf("P: %i\n",(int)P); 
		printf("I: %i\n",(int)I);
		printf("u: %u\n",(int)u);  
		

		char cp[] = "123.34";
		double t =  atof(cp + 1);
		printf("s2d: %lf \n", t);
		snprintf(send_buff, 100, "%lf", t);
		printf("string buffer %s \n",cp);
		
	// reguler 

		//send
		

		//printf("h \n");
		//udpconn_send(conn, send_buff);

	}

	//pthread_join(threadHandle, NULL);
	return 0;

}








#include "../miniproject-files/network/udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>


#define true	(1)

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
	char rcv_buff[100];;

	
	UDPConn* conn = udpconn_new("10.100.23.253", 9999);

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
	printf("START\n"); 
		
	while(1) {

		

		udpconn_send(conn, "GET");
		usleep(1000); 
		dt = 0.001; 
		udpconn_receive(conn,rcv_buff,buflen);
		
		y = atof(rcv_buff + 8);
		printf("rcv buff: %s \n", rcv_buff);  
		P = y;
		I+= (y*dt);
		u = P*Kp + (I*Ki);

		snprintf(send_buff, 100, "%lf", (-u));

		udpconn_send(conn, send_buff);
		printf("y: %lf\n", y); 
		printf("P: %lf\n",P); 
		printf("I: %lf\n",I);
		printf("u: %lf\n",u);  
		


//		char cp[] = "123.34";
//		double t =  atof(cp + 1);
	//	printf("s2d: %lf \n", t);
	//	snprintf(send_buff, 100, "%lf", t);
	//	printf("string buffer %s \n",cp);
		
	// reguler 

		//send
		

		//printf("h \n");
		//udpconn_send(conn, send_buff);

	}

	//pthread_join(threadHandle, NULL);
	return 0;

}








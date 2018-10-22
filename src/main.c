#include "../miniproject-files/network/udp.h"
#include <stdio.h>
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

	

	char send_buff[100];
	int buflen = 100;
	send_buff[0] = "sent";
	char rcv_buff[100];;

	
	UDPConn* conn = udpconn_new("10.100.23.253", 9999);

	udpconn_send(conn, "START");
	udpconn_send(conn, "GET");
	printf("Q\n");
	udpconn_receive(conn,rcv_buff,buflen);

	long ref = 0;
	long I = 0;
	
	long Kp = 10;
	long Ki = 800;

	long y,P,dt, oldT;
	long u; 
	 
	
	
	
	// pthread_t threadHandle;
	// pthread_create(&threadHandle, NULL, fn, NULL);

	
	
	
	while(1) {

		
		printf("main got %s \n", rcv_buff);
		udpconn_send(conn, "GET");
		usleep(10); 
		dt = 10; 
		udpconn_receive(conn,rcv_buff,buflen);
		
		y = str2long(rcv_buff); 
		P = y;
		I+= (y*dt)/1000000;
		u = P*Kp + (I*Ki);
		l2s((-u), send_buff);

		udpconn_send(conn, send_buff);
		printf("y: %i\n", (int)y); 
		printf("P: %i\n",(int)P); 
		printf("I: %i\n",(int)I); 
		
		
	// reguler 

		//send
		

		//printf("h \n");
		//udpconn_send(conn, send_buff);

	}

	//pthread_join(threadHandle, NULL);
	return 0;

}








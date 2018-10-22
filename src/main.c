#include "../miniproject-files/network/udp.h"
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>


#define true	(1)

void* fn(void* args){
	char rcv_buff[100] = "Thread \n";
	int buflen = 100;
	
	UDPConn* conn = udpconn_new("127.0.0.1", 9999);

	while(1){
		printf("a \n");
		udpconn_receive(conn, rcv_buff,100);
		//printf(rcv_buff);
		printf("a \n");
	}

	return NULL;
} 



int main(){


	char send_buff[100];
	int buflen = 100;
	send_buff[0] = "sent";	
	
	UDPConn* conn = udpconn_new("127.0.0.1", 9999);
	udpconn_send(conn, "START");
	
	
	pthread_t threadHandle;
	pthread_create(&threadHandle, NULL, fn, NULL);
	


	while(1) {
		//printf("h \n");
		udpconn_send(conn, send_buff);

	}

	pthread_join(threadHandle, NULL);
	return 0;

}


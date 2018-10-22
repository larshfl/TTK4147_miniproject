#include "../miniproject-files/network/udp.h"
#include <stdio.h>

#include "udp.h"

#define true	(1)


int main(){

	char rcv_buff[100];
	char send_buff[100];
	int buflen = 100;

	send_buff[0] = "sent";	

	UDPConn* conn = udpconn_new("127.0.0.1", 9999);
	udpconn_send(conn, "START");


	while(true) {
		printf("h \n");
		udpconn_send(conn, send_buff);
printf("h \n");
		udpconn_receive(conn, rcv_buff,100);
printf("h \n");
		
		printf(rcv_buff);

	}
	



	return 0;

}


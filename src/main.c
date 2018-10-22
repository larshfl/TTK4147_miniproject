#include "udp.h"
#include "stdio.h"
#include "string.h"
#define true	(1)
#define false   (0)


int main(){

	char rcv_buff[100];
	char send_buff[100];
	int buflen = 100;
	memcpy( send_buff, "sent", sizeof(char)*6);
	// send_buff[0] = "sent";	

	UDPConn* conn = udpconn_new("10.100.23.253", 9999);
	udpconn_send(conn, "START");


	while(true) {
		printf("h \n");
		udpconn_send(conn, send_buff);
printf("h \n");
		udpconn_receive(conn, rcv_buff,100);
printf("h \n");
		
		printf("%s\n", rcv_buff);

	}
	




	return 0;

}


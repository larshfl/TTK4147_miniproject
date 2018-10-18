#include "udp.h"

#define true	(1)


int main(){

	char rcv_buff[100];
	char send_buff[100];
	int buflen = 100;

	UDPConn* conn = udpconn_new("10.100.23.253", 9999);
	udpconn_send(conn, "START");


	while(true) {
		udpconn_send(conn, "GET");
		udpconn_receive(conn, rcv_buff,100);

	}
	




	return 0;

}

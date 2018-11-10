
#include "sharedVariables.h"
#include "stdio.h"

// To delete 




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






//

void* receiver_main(void* args){
	char rcv_buff[100] = "Thread \n";
	int buflen = 100;
	
    
	printf("START_DATA\n"); 
	udpconn_send(CONN, "START");
	udpconn_send(CONN, "GET");
	printf("Q\n");

	
	while(1){
		//printf("REC\n");
        udpconn_receive(CONN,rcv_buff,buflen);
        //printf("%s\n", rcv_buff); 
        if(rcv_buff[0] == 'G'){
            // Reg 
            //pthread_mutex_lock(&Y_LOCK);
            Y= atof(rcv_buff + 8);
            //pthread_mutex_unlock(&Y_LOCK); 
            

        
        }
        else{
            // Signal 
            udpconn_send(CONN, "SIGNAL_ACK");
            //sem_post(&SIG_SEM); 
        }

        
	}

	return NULL;
} 

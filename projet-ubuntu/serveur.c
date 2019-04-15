#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>


#define PORT 8080

int number;
int Price=200;

struct sockaddr_in newAddr;

char buffer[1024];
char Price_buff[10];
char Product_buff[100];
int n,i=0,k ; 

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;


void *host_client( void *variable)
{


	int new_socket=*((int*)variable);
  	 int  num=number;
     	k=number;


      while(1)
                {if(number>2)
                   break;
                 }
			
			while(1){

       
       
             pthread_mutex_lock (&mutex);
            


             




            if(k==1)
        { 
		// send -1 to client so he will know that he won 
		n =send(new_socket,"-1",255,0);  
           	printf("Client won ");
        	pthread_mutex_unlock (&mutex); // after having a winner unlock thee mutex unless continue the work 
         break;
	}

              
                
           
               
             
             sprintf(Price_buff, "%d", Price); // transefer the  value of price into string  so we will send it to the clinet 
             
           n =send(new_socket,Price_buff,255,0);
		 

           bzero(buffer,256);

           n = recv(new_socket,buffer,255,0); // recive the new value from client 
       // if  client  sent something than a number  he will be  out 
              
            if(0 ==atoi(buffer)){
              bzero(buffer,256);
             n =send(new_socket,"out",255,0);
               
                k--;
          pthread_mutex_unlock (&mutex);
           close(new_socket);
             break;
                 } 
           
           Price=Price+atoi(buffer);
                   
           printf("Client  %d : %d\n",num,Price);
             
       

    
          pthread_mutex_unlock (&mutex);

     sleep(1); 
 }


			}
		








int main(int argc,char* argv[] ){

//declartion thread
	pthread_t h_client[10];

	struct sockaddr_storage th;


	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int newSocket;
	

	socklen_t addr_size;

	
	//creating socket 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
		/* getiing data from user darling */ 
				printf (" the Product name please ==== \n ") ;
				scanf ("%s",Product_buff) ; 
				printf (" the price please ===== \n ") ; 
				scanf  ("%d",&Price) ; 
				printf  ( " the bet will start now \n the product name is ===== %s \t the pric is ======%d  \n ",Product_buff,Price);

		/* end getting data from  user */ 
	if(sockfd < 0){
		printf("-****Error in connection.****-\n");
		exit(1);
	}
	printf("  Connected ^_^ \n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("-****Errore in binding.****-\n");
		exit(1);
	}
	printf("  Waiting for clients . \n ");

	

	if(listen(sockfd, 2) == 0){
		printf("Listening....:)\n");
	}else{
		printf("-****Errore in binding.****-\n");
	}
		
		
if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex is off :( \n"); 
        return 1; 
    }



	while(1){

		addr_size=sizeof th;
		newSocket = accept(sockfd, (struct sockaddr*)&th ,&addr_size);
		if(newSocket < 0){
			exit(1);}
           
			//create of thread
			if(pthread_create(&h_client[number],NULL,(void*)host_client,&newSocket)!=0)
                       close(sockfd);


	
		        number++;
		

	}

	close(newSocket);


	return 0;
}

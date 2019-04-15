#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("cant connect :( \n");
		exit(1);
	}
	printf("Waiting...\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // put the client ip so we can connect to the same  network

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("cant connect :( \n");
		exit(1);
	}
	printf("Welcome to the BET\n");

	int nb;

	while(1)
    {
                
 while(recv(clientSocket,buffer,255,0) < 0 );
              

if(atoi(buffer)== -1){
                  printf("You Won \n");
                     return 0;} 

                 if(strcmp(buffer,"out")==0){
                  printf(" GOOD Bye \n");
                     return 0;}

                     if(atoi(buffer)>0){
                     

                   

       
                 printf(" current Price = : %s\n",buffer);

        bzero(buffer,256);
		
	printf("  to bet more add a number to quite just  type out  \n ") ; 


        fgets(buffer,255,stdin);
        nb = send(clientSocket,buffer,strlen(buffer),0);

        if (nb< 0) {
             printf("ERROR writing to socket");
                  break;}


        }
            
 bzero(buffer,256);
   
 }


    close(clientSocket);



return 0;
}

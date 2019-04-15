
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <signal.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#define MAX 80 
#define PORT    "8080" /* Port to listen on */
#define BACKLOG     10  /* Passed to listen() */




GtkWidget *window;
GtkWidget *div1;
GtkWidget *div12;
GtkWidget *div3;
GtkWidget *div4;
GtkWidget *start;
GtkWidget *end;
GtkWidget *title;
GtkWidget *enter1;
GtkWidget *enter2;
GtkWidget *prix;
GtkWidget *nomp;
GtkWidget *textvue;
GtkWidget *server 
GtkBuilder *builder;

GtkTextBuffer *ch;
  GtkTextIter start, end;
  GtkTextIter iter;
/******** we will put our program here ^^ ****************************/ 
int i = 0 ;
char product [MAX] ; 
	int price ; 
void *handle(void *pnewsock)
{
    /* send(), recv(), close() */
		char buff[MAX];
		char buff2[MAX]; 
		char buff3[MAX];
		int  connfd =  *((int *) pnewsock) ;
		 strcpy(buff2, product);
		 sprintf(buff, "%d", price);

		printf(" client %d  \n ",i) ; 
		/* write */ 
	 	write(connfd, buff2, sizeof(buff2));
	 	bzero(buff2, MAX);
		
		write(connfd, buff, sizeof(buff));
	 	bzero(buff, MAX);
	 	
		
		
		/*write*/
				
		/*read 
			read(connfd, buff3, sizeof(buff3)); 
		  	printf(" Client %d have  bet with   : %s", i, buff3); 
		read*/		

		
		
			
    		free(pnewsock);
 		pthread_exit(NULL);
 
    
}
 
void ser(GtkWidget *start, gpointer data)
{
    int sock;
    pthread_t thread[50];
    struct addrinfo hints, *res;
    int reuseaddr = 1; /* True */
	
 
/****** auction *********/
			printf(" Welcome to the auction  Serveur \n" ) ; 
		 	
 			 	srtcpy ( product  ,gtk_entry_get_text(GTK_ENTRY(enter2)) ) ;
		 
			   	 price = atoi((char *)gtk_entry_get_text(GTK_ENTRY(enter2)));
			printf ( " product : %s \n price : %d \n ", product,price ) ;   
	

/****** auction *********/

    /* Get the address info */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(NULL, PORT, &hints, &res) != 0) {
        perror("getaddrinfo");
        return 1;
    }
 		
	
	
	
    /* Create the socket */
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        perror("socket");
        return 1;
    }	
	printf(" the socket was created \n" ) ; 
 
    /* Enable the socket to reuse the address */
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1) {
        perror("setsockopt");
        return 1;
    }
 
    /* Bind to the address */
    if (bind(sock, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        return 0;
    }
 
    freeaddrinfo(res);
 
    /* Listen */
    if (listen(sock, BACKLOG) == -1) {
        perror("listen");
        return 0;
    }
	
  
    /* Main loop */
    while (1) {
        socklen_t size = sizeof(struct sockaddr_in);
        struct sockaddr_in their_addr;
        int newsock = accept(sock, (struct sockaddr*)&their_addr, &size);
        if (newsock == -1) 
	{
		//if u didnt had connection
            perror("accept");
        }
        else 
	{
		// if u had connection 
            	printf("Got a connection from %s on port %d\n", inet_ntoa(their_addr.sin_addr), htons(their_addr.sin_port));
            	/* Make a safe copy of newsock */
            int *safesock = malloc(sizeof(int));
            if (safesock) 
	    {
		// if the socket worked 
                *safesock = newsock;
                if (pthread_create(&thread[i], NULL, handle, safesock) != 0) 
		{
			// if thread didnt work 
                    	fprintf(stderr, "Failed to create thread\n");
			
                }	

				// if thread worked 	
			printf("thread was created with succes %d ",i) ;	
			pthread_join (thread[i], NULL) ; 

				
				


            	}
            else 
	    {
		//if the socket didnt work 
                perror("malloc");
            }
		
        }
i++ ; 
    }
 
    close(sock);
 
    return 0;
}




















/******** we will put our program here ^^ ****************************/ 

int main (int argc,char *argv[]){
gtk_init(&argc,&argv);



builder=gtk_builder_new_from_file("INTERFACE.glade");
window=GTK_WIDGET(gtk_builder_get_object(builder,"window"));
g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);

gtk_builder_connect_signals(builder,NULL);
div1=GTK_WIDGET(gtk_builder_get_object(builder,"div1"));
div12=GTK_WIDGET(gtk_builder_get_object(builder,"div12"));
div3=GTK_WIDGET(gtk_builder_get_object(builder,"div3"));
div4=GTK_WIDGET(gtk_builder_get_object(builder,"div4"));

start=GTK_WIDGET(gtk_builder_get_object(builder,"start"));
end=GTK_WIDGET(gtk_builder_get_object(builder,"end"));
title=GTK_WIDGET(gtk_builder_get_object(builder,"title"));
enter1=GTK_WIDGET(gtk_builder_get_object(builder,"enter1"));
enter2=GTK_WIDGET(gtk_builder_get_object(builder,"enter2"));

prix=GTK_WIDGET(gtk_builder_get_object(builder,"prix"));
nomp=GTK_WIDGET(gtk_builder_get_object(builder,"nomp"));

textvue=GTK_WIDGET(gtk_builder_get_object(builder,"textvue"));

gtk_widget_show(window);
gtk_main();

g_signal_connect(start, "clicked", G_CALLBACK(ser), NULL);
return EXIT_SUCCESS ;

}



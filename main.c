#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<time.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

#define CLI_VERSION "0.2.6"


char* getTime(){
	char *finalTime;
	char timeStr[1000];

	time_t t = time(NULL);
	struct tm * p = localtime(&t);

	strftime(timeStr, 1000, "%d/%m/%Y-%k:%M:%S", p);
	finalTime = timeStr + '\0';

	return finalTime;
}

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[10];

	

	printf("=========================\n");
	printf("netbenixCMD Server\n");
	printf("Version: %s\n", CLI_VERSION);
	printf("=========================\n");

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("[%s] Could not create socket\n", getTime());
	}
	printf("[%s] Socket created\n", getTime());
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 34000 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		printf("[%s] Bind failed. Error\n", getTime());
		return 1;
	}
	printf("[%s] Bind done\n", getTime());
	
	//Listen
	listen(socket_desc , 3);
	while(1){
		//Accept and incoming connection
		printf("[%s] Waiting for incoming connections...\n", getTime());
		c = sizeof(struct sockaddr_in);
	
		//accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0)
		{
			printf("[%s] Accept failed\n", getTime());
			return 1;
		}
		printf("[%s] Connection accepted\n", getTime());
	
		//Receive a message from client
		while( (read_size = recv(client_sock , client_message , 10 , 0)) > 0 )
		{
    	    char version_ok[2000] = "VERSION_OK";
			char version_old[2000] = "VERSION_OUTDATED";
    	    if(!strcmp(client_message, CLI_VERSION)){
    	        write(client_sock , version_ok, strlen(version_ok));
    	    } else {
    	        write(client_sock , version_old, strlen(version_old));
    	    }
			//Send the message back to client
			memset(client_message, 0, sizeof(client_message));
		}
	
		if(read_size == 0)
		{
			printf("[%s] Client disconnected\n", getTime());
			fflush(stdout);
		}
		else if(read_size == -1)
		{
			printf("[%s] Recv failed\n", getTime());
		}
	}
	
	
	return 0;
}


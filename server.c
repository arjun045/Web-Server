#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <unistd.h>
#include<signal.h>
#include<string.h>

int a[10]={0};

typedef struct
{
	char name[100];
	int sock;
	struct sockaddr address;
	int addr_len;
} connection_t;

void * process(void * ptr)
{
	char * buffer;
	int len,i,name;
	connection_t * conn;
	long addr = 0;
	char content[100];
	if (!ptr) pthread_exit(0); 
	conn = (connection_t *)ptr;

	if(fork())
    {
        //printf("\nEnter the data to be send type exit for stop:\n");
        scanf("%d %s",&name,content);
        while(strcmp(content,"exit")!=0)
        {
            send(a[name],content,100,0);
            scanf("%d %s",&name,content);
        }

        send(a[name],"exit",5,0);
    }
    else
        i = recv(conn->sock,content,100,0);

    while(strcmp(content,"exit")!=0)
    {
        printf("\nClient:%s %s\n",conn->name,content);
        i=recv(conn->sock,content,100,0);
    }

    printf("\nBye %s",conn->name);
    //send(conn->sock,"Offline",10,0);
	

	 //close socket and clean up 
	close(conn->sock);
	free(conn);
	pthread_exit(0);

}

int main(int argc, char ** argv)
{
	int sock = -1,i;
	struct sockaddr_in address;
	int port,p=0;
	connection_t * connection;
	pthread_t thread;

	/* check for command line arguments */
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s port\n", argv[0]);
		return -1;
	}

	/* obtain port number */
	if (sscanf(argv[1], "%d", &port) <= 0)
	{
		fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
		return -2;
	}

	/* create socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
		return -3;
	}

	/* bind socket to port */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
	{
		fprintf(stderr, "%s: error: cannot bind socket to port %d\n", argv[0], port);
		return -4;
	}

	/* listen on port */
	if (listen(sock, 5) < 0)
	{
		fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
		return -5;
	}

	printf("%s: ready and listening\n", argv[0]);
	
	while (1)
	{
		/* accept incoming connections */
		connection = (connection_t *)malloc(sizeof(connection_t));
		connection->sock = accept(sock, &connection->address, &connection->addr_len);
		if (connection->sock <= 0)
		{
			free(connection);
		}
		else
		{
		
			i = recv(connection->sock,connection->name,99,0);
			printf("Hello %s\n",connection->name);
			p++;
			if(a[p]==0){
			a[p]=connection->sock;
			pthread_create(&thread, 0, process, (void *)connection);
			pthread_detach(thread);
			}else{
			free(connection);			//printf("%d\n",p);
			/* start a new thread but do not wait for it */
}
			}
	}
	
	return 0;
}

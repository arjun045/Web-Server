#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
int main(int argc, char ** argv)
{
	int port,i,k;
	int sock = -1;
	struct sockaddr_in address;
	struct hostent * host;
	int len;
	char content[100];
	//char name[4][10]={"Arjun","Gaurav","Dev","Ayush"};
	
//printf("%d",argc);
	/* checking commandline parameter */
	if (argc != 4)
	{
		printf("usage: %s hostname port text\n", argv[0]);

		return -1;
	}

	/* obtain port number */
	if (sscanf(argv[2], "%d", &port) <= 0)
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

	/* connect to server */
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	host = gethostbyname(argv[1]);
	if (!host)
	{
		fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
		return -4;
	}
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
	{
		fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
		return -5;
	}

	/* send text to server */
	len = strlen(argv[3]);
	//write(sock, &len, sizeof(int));
	send(sock, argv[3], len,0);
	if(fork())
    {
        printf("\nEnter the data to be send type exit for stop:\n");
        scanf("%s",content);

        while(strcmp(content,"exit")!=0)
        {
            send(sock,content,100,0);
            scanf("%s",content);
        }
        send(sock,"exit",5,0);
    }
    else
    {
        i=recv(sock,content,100,0);

        while(strcmp(content,"exit")!=0)
        {
            printf("\nServer: %s\n",content);
            i=recv(sock,content,100,0);
        }
        send(sock,"exit",5,0);
    }
	/* close socket */

	close(sock);

	return 0;
}

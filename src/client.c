#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define PORT        5000
             /* REPLACE with your server machine name*/
#define HOST        "192.168.1.2"
#define DIRSIZE     8192

tcp(int argc, char argv[2][100])
//int argc; char **argv;
{
	printf("%s",argv[1]);
        char hostname[100];
	char    dir[DIRSIZE];
	//char* data = "takeoff()";
	int	sd;
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	struct hostent *hp;

        strcpy(hostname,HOST);
        if (argc>2)
            { strcpy(hostname,argv[2]); }

	/* go find out about the desired host machine */
	if ((hp = gethostbyname(hostname)) == 0) {
		perror("gethostbyname");
		exit(1);
	}

	/* fill in the socket structure with host information */
	memset(&pin, 0, sizeof(pin));
	pin.sin_family = AF_INET;
	pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	pin.sin_port = htons(PORT);

	/* grab an Internet domain socket */
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* connect to PORT on HOST */
	if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) {
		perror("connect");
		exit(1);
	}

	/* send a message to the server PORT on machine HOST */
	if (send(sd, argv[1], strlen(argv[1]), 0) == -1) {
		perror("send");
		exit(1);
	}

        /* wait for a message to come back from the server 
        if (recv(sd, dir, DIRSIZE, 0) == -1) {
                perror("recv");
                exit(1);
        }*/

        /* spew-out the results and bail out of here! 
        printf("%s\n", dir);

	close(sd);*/
}

sendCommand(char* cmd){
	printf("c");
	printf("c%s", cmd);
	char argv[2][100];
	strcpy(argv[1],cmd);
	printf("%s", argv[1]);
	tcp(2,argv);
 }

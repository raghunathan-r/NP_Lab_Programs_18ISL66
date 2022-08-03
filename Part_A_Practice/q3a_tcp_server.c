// Basic header files needed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Header files required for socket programming
#include <sys/types.h>          // has all the data types used during system calls
#include <sys/socket.h>         // has definations and structures for socket programming
#include <netinet/in.h>         // contains strutures for storing domian addresses

int main(int argc, char *argv[]){

    if(argc < 2){ printf("\ninvalid port number provided\n"); exit(1);}

    // now the varibales we require
    int sockfd, newsockfd, portno, n;
    char buffer[255];

    struct sockaddr_in server_addr, cli_addr;   // sockaddr_in has the all the related information of the socket
    socklen_t clilen;           // its a 32 bit data type used to store length of address

    // creting the socket
    /*
        int sockfd = socket(int domain, int type, int protocol)

        domain -> is IPV4 so we specify AF_INET
        type -> it is type of connection SOCK_STREAM for TCP and SOCK_DGRAM for datagram protocol UDP
        protocol -> 0 for the default protocol for IPV4
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) { printf("\nERROR creating socket\n"); exit(1); }

    // clearning the data in the varibale so we dont have grabage values
    bzero((char *) &server_addr, sizeof(server_addr));

    portno = atoi(argv[1]);             // atoi() is used for converting string to integer

    // filling the related information of the socket address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);       // htons() is called host to network short

    // bindinding the socket with the socket address
    n = bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if(n < 0) { printf("\nERROR binding socket\n"); exit(1);};

    // listening to any client that wants to make a connection
    listen(sockfd, 5);                  // int listen(int sockfd, int backlog)
    clilen = sizeof(cli_addr);

    // getting the sockfd of the client that has made the connection
    newsockfd = accept(sockfd, (struct sockaddr *) & cli_addr, &clilen);
    if(newsockfd < 0) { printf("\nERROR accepting request\n"); }

    // now communicating between the cleint and sever
    while(1){

        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255);
        if(n < 0) { printf("\nERROR reading data\n"); }
        printf("client : %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, 255);
        if(n < 0) { printf("\nERROR writting data\n"); }

        int i = strncmp("bye", buffer, 3);
        if( i == 0)
        break;
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}

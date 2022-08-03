/*
    input : filename server_ipaddress portno
*/

// Basic header files needed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Header files required for socket programming
#include <sys/types.h>          // has all the data types used during system calls
#include <sys/socket.h>         // has definations and structures for socket programming
#include <netinet/in.h>         // contains strutures for storing domian addresses
#include <unistd.h>             // required to perform read() and write() functions

// Hederfiles required in client side are
#include <netdb.h>              // this defines the struct hostent

int main(int argc, char *argv[]){

    if(argc < 3){ printf("\ninvalid port number provided\n"); exit(1);}

    // now the varibales we require
    int sockfd, newsockfd, portno, n;
    char buffer[255];

    struct sockaddr_in server_addr;   // sockaddr_in has the all the related information of the socket
    socklen_t clilen;           // its a 32 bit data type used to store length of address

    struct hostent *server;     // used to store information about the given host

    // creting the socket
    /*
        int sockfd = socket(int domain, int type, int protocol)

        domain -> is IPV4 so we specify AF_INET
        type -> it is type of connection SOCK_STREAM for TCP and SOCK_DGRAM for datagram protocol UDP
        protocol -> 0 for the default protocol for IPV4
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) { printf("\nERROR creating socket\n"); exit(1); }

    portno = atoi(argv[2]);             // atoi() is used for converting string to integer

    // getting information regadring the server from the ip address
    server = gethostbyname(argv[1]);
    if(server == NULL){ printf("\nERROR invalid ip address"); }

    bzero((char *) & server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);          // bcopy function copies n bytes
    server_addr.sin_port = htons(portno);

    n = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if(n < 0) { printf("\nERROR unable to connect\n"); }

    while(1){

        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if(n < 0) { printf("\nERROR in writting\n"); }

        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);
        if(n < 0) { printf("\nERRO in reading\n"); }
        printf("server : %s\n", buffer);

        int i = strncmp("bye", buffer, 3);
        if( i == 0)
        break;
    }

    close(sockfd);
    return 0;
}

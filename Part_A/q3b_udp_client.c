// Q3B. Design a C program to implement Client server model (UDP) using socket programming.

// UDP Client

    // TILL HERE IT IS THE SAME CODE FOR CLIENT AND SERVER ALSO


#include<stdio.h>
// the below header file is used to add address structures for the sockets
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>


// #include <stdio.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <string.h>

int main(){

    // since we are going to run the application on the same machine we are going to use the localhost port 5500 [ it can be anything greater than 5000 ] and an ip address of 127.0.0.1 [ you can get this by typing ' ifconfig' in terminal ]
    char *ip = "127.0.0.1";
    int port = 5500;

    // now we are going to declare structures and variables for the client and server sockets
    int server_sock, client_sock;
    // using the <arpa/inet.h> header file we get the structures
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    
    // now to transfer the information we will use a buffer
    char buffer[1024];
    int n;

    // now we will have to create a UDP socket. 
    // for this we will use the SOCK_DGRAM protocol cause its UDP and AF_INET cause we are using IPV4 protocol. 0 is for using default protocol I guess
    client_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // now we check if the server socket is properly created
    if(client_sock < 0){
        printf("socket error!\n");
    } else{
        printf("udp server socket created !\n");
    }

    // now we provide the UDP server socket some information regarding the structure
    // memset is included in the <string.h> header file. what it does is fills the memory with a constant byte c. in this case the server_addr is made 000000 for safety precautions.
    memset(&server_addr, '\0', sizeof(client_addr));
    // now give the server address some information regarding its family
    // AF_INET means it is from the IPV4 protocol. The port number which we already saved as 5500 and the ip address which we had also saved.
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    // what inet_addr does it, it converts the ip address from the . dot notion into binary format
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // TILL HERE IT IS THE SAME CODE FOR CLIENT AND SERVER ALSO

    do{

        bzero(buffer, 1024);

        // take message that has to be sent to the server
        printf("\nclient says ? : "); gets(buffer);
        // sending the message from the client to the server
        sendto(client_sock, buffer, 1024, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        printf("\n-> message sent from server - %s\n", buffer);

        // receiving message from the server
        bzero(buffer, 1024);
        int len = recvfrom(client_sock, buffer, 1024, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        // recvfrom(client_sock, buffer, 1024, 0, NULL, NULL);
        printf("\nlen = %d\n", len);
        printf("\nreceived messages -> %s\n", buffer);

    } while(0);

    return 0;

}
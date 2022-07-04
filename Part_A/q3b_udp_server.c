// Q3B. Design a C program to implement Client server model (UDP) using socket programming.

// UDP Server

/*
    THEORY

    - https://www.geeksforgeeks.org/socket-programming-cc/
    - https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
    - https://www.geeksforgeeks.org/udp-server-client-implementation-c/

    - it doesn't form a connection with the server like UDP does
    - it just send a datagram
    - server doesn't have to connect, it just waits for the datagram



*/


#include<stdio.h>
// the below header file is used to add address structures for the sockets
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>


// #include <stdio.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <string.h>
// #include <stdlib.h>

int main(){

    // since we are going to run the application on the same machine we are going to use the localhost port 5500 [ it can be anything greater than 5000 ] and an ip address of 127.0.0.1 [ you can get this by typing ' ifconfig' in terminal ]
    char *ip = "127.0.0.1";
    int port = 5500;

    // now we are going to declare structures and variables for the client and server sockets
    int server_sock, client_sock;
    // using the <arpa/inet.h> header file we get the structures
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // I AM DOING THIS CAUSE SERVER IS NOT SENDING DATA
    struct sockaddr_storage server_storage;
    
    // now to transfer the information we will use a buffer
    char buffer[1024];
    int n;

    // now we will have to create a UDP socket. 
    // for this we will use the SOCK_DGRAM protocol cause its UDP and AF_INET cause we are using IPV4 protocol. 0 is for using default protocol I guess
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // now we check if the server socket is properly created
    if(server_sock < 0){
        printf("socket error!\n");
    } else{
        printf("udp server socket created !\n");
    }

    // now we provide the UDP server socket some information regarding the structure
    // memset is included in the <string.h> header file. what it does is fills the memory with a constant byte c. in this case the server_addr is made 000000 for safety precautions.
    memset(&server_addr, 0, sizeof(server_addr));
    // now give the server address some information regarding its family
    // AF_INET means it is from the IPV4 protocol. The port number which we already saved as 5500 and the ip address which we had also saved.
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    // what inet_addr does it, it converts the ip address from the . dot notion into binary format
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // now we will bind the information and ip and port number of the server socket
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // now we check if the socket is properly done binding
    if(n < 0){
        printf("\nerror in binding\n"); exit(1);
    }else{
        printf("\nbinding server socket successfully with port : %d\n", port);
    }

    // now that we have successfully done binding the address and information
    // we are going to listen for any requests done by clients
    listen(server_sock, 5);
    printf("listening ...\n");

    // now we are going to continuously listen for any requests from client we put it in an infinite loop
    do{
        
        // in UDP we DONT NEED TO CONNECT TO a CLIENT we just have to wait for datagrams being sent

        // bzero(buffer, 1024);
        // recvfrom(server_sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

        
        bzero(buffer, 1024);
        recvfrom(server_sock, buffer, 1024, 0, (struct sockaddr*)&server_storage, sizeof(server_storage));


        // displaying the received message that is stored in the buffer
        printf("client sent message -> %s\n", buffer);

        // // sending a message to the client
        // bzero(buffer, 1024);
        // printf("server says ? : "); gets(buffer);
        // sendto(server_sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

        // TRYING TO SEND MESSAGE TO CLIENT USING struct sockaddr_storage
        // sending a message to the client
        bzero(buffer, 1024);
        printf("server says ? : "); gets(buffer);
        printf("\nyou have entered : %s\n", buffer);
        sendto(server_sock, buffer, 1024, 0, (struct sockaddr*)&server_storage, sizeof(server_storage));


        // since we not making any connection we dont have to close any sockets
    } while(0);





    return 0;
}
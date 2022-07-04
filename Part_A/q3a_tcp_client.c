// Q3A. Design a C program to implement Client server model (TCP) using socket programming.

// TCP Client

/*
    - first write the server code
    - then copy the major part of the code as it is the same for client also
*/

    // TILL HERE IT IS THE SAME FOR CLIENT AND SERVER ALSO


#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){

    // since we are going to run the application the same machine we use the localhost port [ any port greater than 5000 ] 127.
    char *ip = "127.0.0.1";
    int port = 5500;

    // now we declare the variable and structure for the socket
    int sock;
    // this is present inside the #include<arpa/inet.h> header file
    struct sockaddr_in client_addr;
    socklen_t addr_size;
    // now to transfer the information we will use a buffer
    char buffer[1024];
    int n;

    // now creating the TCP server socket
    // here SOCK_STREAM refers to the TCP protocol
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // checking if the socket if properly created
    if(sock < 0){
        printf("socket error !\n"); exit(1);
    } else{
        printf("tcp server socket created !\n");
    }

    // now providing the TCP socket some information regarding the structure
    // for this we need to include #include<string.h>
    memset(&client_addr, 0, sizeof(client_addr));
    // here AF_INET means internet version 4
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = port;
    client_addr.sin_addr.s_addr = inet_addr(ip);

    // TILL HERE IT IS THE SAME FOR CLIENT AND SERVER ALSO

    // in the client we just need to connect to the server. no need to bind
    connect(sock, (struct sockaddr*)&client_addr, sizeof(client_addr));
    printf("connected to server\n");

    while(1) {
        // now that we have connected we can start sending messages
        // we use the buffer to store our messages

        bzero(buffer, 1024);
        strcpy(buffer, "hello there, server. this is client\n");
        printf("-> report : client sent - %s\n", buffer);

        // now we send the message using the send function
        send(sock, buffer, strlen(buffer), 0);

        // now taking care of the messages received form the server
        bzero(buffer, 1024);
        recv(sock, buffer, sizeof(buffer), 0);
        printf("server : %s\n", buffer);

    }

    // now after all the messages are transmitted we are going to disconnect from the server
    close(sock);
    printf("disconnected from the server\n");


    return 0;
}
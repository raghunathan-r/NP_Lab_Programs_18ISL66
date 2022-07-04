// Q3A. Design a C program to implement Client server model (TCP) using socket programming.

// TCP server

/*
    - this is suited for functions that need high reliability
    - there is absolute guarantee that the data transferred remains intact and arrives in the same order in which it was sent
    - handles reliability and congestion control
    - does error checking and error recovery

    Algorithm
    1. create a socket
    2. bind the socket
    3. listen for a client
    4. accept the client
    5. send receive messages
    6. close the socket
*/

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
    int server_sock, client_sock;
    // this is present inside the #include<arpa/inet.h> header file
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    // now to transfer the information we will use a buffer
    char buffer[1024];
    int n;

    // now creating the TCP server socket
    // here SOCK_STREAM refers to the TCP protocol
    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    // checking if the socket if properly created
    if(server_sock < 0){
        printf("socket error !\n"); exit(1);
    } else{
        printf("tcp server socket created !\n");
    }

    // now providing the TCP socket some information regarding the structure
    // for this we need to include #include<string.h>
    memset(&server_addr, 0, sizeof(server_addr));
    // here AF_INET means internet version 4
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // now we will mind the address and the port number
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // now checking it the socket is properly binding
    if(n < 0){
        printf("\nerror in binding\n"); exit(1);
    } else{
        printf("\nbinding socket successfully port : %d\n", port);
    }

    // now that we have successfully bound the port number
    // we are going to listen for the client. here 5 means 5 clients
    listen(server_sock, 5);
    printf("listening ...\n");

    // now we will only connect to one client at a time
    while (1){
        // in this we need to accept connections from the client
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        printf("client connected\n");

        do{
            // now we accept the messages received from the client into the buffer variable
            bzero(buffer, 1024);
            recv(client_sock, buffer, sizeof(buffer), 0);
            printf("client : %s\n", buffer);

            // sending a message to the client
            bzero(buffer, 1024);
            
            // accepting a message a sent form server
            gets(buffer);
            printf("-> report : server sent - %s\n", buffer);
            send(client_sock, buffer, strlen(buffer), 0);

        } while(strcmp(buffer, "exit") == 0);

        // closing the connection after all the messages are transferred
        close(client_sock);
        printf("closed client socket\n");

        /*
        // now we accept the messages received from the client into the buffer variable
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("client : %s\n", buffer);

        // sending a message to the client
        bzero(buffer, 1024);
        strcpy(buffer, "hello there, client. this is server\n");
        printf("-> report : server sent - %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        // closing the connection after all the messages are transferred
        close(client_sock);
        printf("closed client socket\n");
        */

        // now because we are in a while loop, it will go back and again wait for a new client to establish a connection.
    }
    

    return 0;
}
// UDP Server program

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
// the recvfrom function is in this header file
#include<sys/socket.h>
#include<netinet/in.h>


int main(){

    // variable for the storing the socket information
    int port = 5500;
    char *ip = "127.0.0.1";

    // creating variables for the server socket and the server address and other things
    int server_sock;
    struct sockaddr_in server_addr, client_addr;

    // creating a server UDP socket. for UDP domain - AF_INET, type - SOCK_DGRAM, protocol - 0
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // DEBUGGING
    if(server_sock < 0){
        printf("\nerror creating server socket!\n"); exit(1);
    } else{
        printf("\nsuccessfully binding server socket\n");
    }

    // clearing the garbage values in the address variables if any
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    // providing the information regrading the server address to the server_addr structure
    server_addr.sin_family = AF_INET;
    // server_addr.sin_port = htons(port);
    server_addr.sin_port = port;
    // server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // binding the socket to the server address
    int n;
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // DEBUGGING
    if(n < 0){
        printf("\nerror binding the server socket and server address!\n"); exit(1);
    } else{
        printf("\nsuccessfully binding the server socket and server address!\n");
    }

    // using an infinite loop so the server can keep listening to other datagrams
    char buffer[1024];

    while(1){
        
        bzero(buffer, 1024);
        socklen_t address_len = sizeof(client_addr);

        // receiving data client
        // int message_len = recvfrom(server_sock, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr*)&client_addr, &address_len);
        int message_len = recvfrom(server_sock, (char *)buffer, 1024, 0, (struct sockaddr*)&client_addr, address_len);

        printf("\nclient says : %s\n", buffer);

    }
    





}

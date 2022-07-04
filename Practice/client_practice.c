// UDP Client

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
// this has the function to close the socket
#include<unistd.h>

int main(){

    // variable for the storing the socket information
    int port = 5500;
    char *ip = "127.0.0.1";

    // creating variables for the server socket and the server address and other things
    int client_sock;
    struct sockaddr_in server_addr, client_addr;

    // creating a server UDP socket. for UDP domain - AF_INET, type - SOCK_DGRAM, protocol - 0
    client_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // DEBUGGING
    if(client_sock < 0){
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

    // THERE IS NO NEED OF BINDING IN THE CLIENT SIDE

    // using an infinite loop so the server can keep listening to other datagrams
    char buffer[1024];

    while(1){
        
        bzero(buffer, 1024);

        // sending data to server
        printf("client says ? : "); fgets(buffer, 1024, stdin);
        sendto(client_sock, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr*)&client_addr, sizeof(client_addr));
        printf("\n-> message sent from client - %s\n", buffer);

        close(client_sock);

    }

}
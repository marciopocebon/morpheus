#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#define AUTHOR "zer0dx"
#define VERSION "0.2"
#define SERVER_PORT 5000
#define SERVER_BACKLOG 2000
#define SERVER_ADDR "192.168.1.3"

int create_socket(){
    int sockfd;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(1);
    }

    printf("[+]Successfully created socket\n");
    return sockfd;
}
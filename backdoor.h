#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

#define AUTHOR "zer0dx"
#define VERSION "0.2"
#define SERVER_BACKLOG 2000

static void show_banner(){

    puts("███╗   ███╗ ██████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██╗   ██╗███████╗");
    puts("████╗ ████║██╔═══██╗██╔══██╗██╔══██╗██║  ██║██╔════╝██║   ██║██╔════╝");
    puts("██╔████╔██║██║   ██║██████╔╝██████╔╝███████║█████╗  ██║   ██║███████╗");
    puts("██║╚██╔╝██║██║   ██║██╔══██╗██╔═══╝ ██╔══██║██╔══╝  ██║   ██║╚════██║");
    puts("██║ ╚═╝ ██║╚██████╔╝██║  ██║██║     ██║  ██║███████╗╚██████╔╝███████║");
    puts("╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚══════╝");
    printf("\nAuthor: %s\n", AUTHOR);
    printf("Version: %s\n\n", VERSION);
}

static void show_help(char *name){
    fprintf(stderr, "[Use]: %s <your address> <port>\nExample: %s 192.168.1.10 5500\n", name, name);
    exit(1);
}

int create_socket(){
    int sockfd;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(1);
    }

    printf("[+]Successfully created socket\n");
    return sockfd;
}

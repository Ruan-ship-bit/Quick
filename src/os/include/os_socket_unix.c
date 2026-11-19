#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "os_socket.h"



socket_t os_socket_create() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if(server < 0) {
        perror("Erro ao Criar Socket");
        return EXIT_FAILURE;
    }
    return server;
}

int os_socket_bind(socket_t sock, int port) {
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in endereco;
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET; 
    endereco.sin_port = htons(port);
    int ouvidor = bind(sock, (struct sockaddr *)&endereco, sizeof(endereco));
    if(ouvidor < 0) {
        perror("Erro");
        close(sock);
        return EXIT_FAILURE;
    }
    return ouvidor;
}
int os_socket_listen(socket_t sock, int backlog) {
    if (listen(sock, backlog) < 0) {
        perror("Erro no listen");
        close(sock);
        return EXIT_FAILURE;
    }
    printf("Aguardando conexões na porta 8080...\n");
    return EXIT_SUCCESS;
}

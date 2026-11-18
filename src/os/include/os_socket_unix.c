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
}
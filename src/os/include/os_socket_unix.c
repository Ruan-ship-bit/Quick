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

socket_t os_socket_accept(socket_t sock) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    socket_t client_fd = accept(sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Erro no accept");
        close(sock);
        return EXIT_FAILURE;
    }
    return client_fd;
}

int os_socket_recv(socket_t sock, char *buffer, int buffer_size) {
    ssize_t bytes_lidos = recv(sock, buffer, buffer_size - 1, 0);

    if (bytes_lidos > 0) {
        buffer[bytes_lidos] = '\0'; // Finaliza a string corretamente;
        printf("Recebido (%zd bytes): %s\n", bytes_lidos, buffer);
        return EXIT_SUCCESS;
    } else if (bytes_lidos == 0) {
        printf("O cliente desconectou.\n");
        return EXIT_FAILURE;
    } else {
        perror("Erro ao receber dados no recv");
        return EXIT_FAILURE;
    }
}

int os_socket_send(socket_t sock, const char *data, int data_size) {
    ssize_t bytes_enviados = send(sock, data, data_size, 0);
    if( bytes_enviados >= 0) {
        printf("Foram enviados %zd bytes.\n", bytes_enviados);
        return EXIT_SUCCESS;
    } else {
        perror("Erro ao enviar a mensagem");
        return EXIT_FAILURE;
    }
}

#pragma once 

// 1. A Tomada Universal (O tipo de dado)
// No Linux, um socket é um int. No Windows, é um tipo especial (SOCKET).
// Nós criamos um "apelido" (typedef) para que o resto do código não se importe.
#ifdef _WIN32
    #include <winsock2.h>
    typedef SOCKET socket_t;
#else
    typedef int socket_t;
#endif

// 2. As Funções Básicas de Rede
// O seu main.c vai chamar essas funções. O os_socket_unix.c vai implementá-las.

// Inicializa a biblioteca de rede (No Linux não faz nada, no Windows liga o WSAStartup)
void os_network_init();

// Cria o "telefone"
socket_t os_socket_create();

// Amarra o telefone na porta
int os_socket_bind(socket_t sock, int port);

// Fica escutando
int os_socket_listen(socket_t sock, int backlog);

// Aceita uma chamada (retorna um novo socket para o cliente)
socket_t os_socket_accept(socket_t sock);

// Lê os dados
int os_socket_recv(socket_t sock, char *buffer, int buffer_size);

// Envia os dados
int os_socket_send(socket_t sock, const char *data, int data_size);

// Fecha o telefone
void os_socket_close(socket_t sock);
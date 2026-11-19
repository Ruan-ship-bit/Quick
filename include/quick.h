#pragma once


typedef enum HTTP_Methods {
    GET =1, //1
    POST, //2
    PUT, //3
    DELETE //4
} HTTP_Methods;

typedef struct Route {
    char* caminho;           
    void (*handler)(void);   
    HTTP_Methods metodos;    
    
} Route;
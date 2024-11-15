#include "server.h"

char* readSocket(SOCKET* sock) {
    const int inpBufferLen = 512;
    char* inpBuffer = malloc(inpBufferLen*sizeof(char));
    ZeroMemory(inpBuffer, inpBufferLen);
    int bytesRead = recv(*sock, inpBuffer, inpBufferLen, 0);
    if (bytesRead < 0) {
        perror("Failed to read from client!\n");
    }
    return inpBuffer;
}

int handleRequest(char* req) {
    // Depending on the request do something
    // Example requests
    // HTML File - From client
        // Response - OK
    // GET request - From browser
        // Responses: OK-here is webpage, 404-not found
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        perror("Number of args inncorrect!\n");
        return 1;
    }
    char* port = argv[1];
    // TODO: check if port is valid
    // WSA Initialisation
    WSADATA wsaData;
    int winSockInitRes = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(winSockInitRes != 0) {
        perror("Failed to init winsock! \n");
        return 1;
    }
    // Creating Server Socket
    struct addrinfo *result = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    int getInfoRes = getaddrinfo(NULL, port, &hints, &result);
    if (getInfoRes != 0) {
        perror("getaddrinfo failed!\n");
        return 1;
    }
    // For listening on the socket:
    SOCKET listener = INVALID_SOCKET;
    listener = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    // Binding the socket
    int bindRes = bind(listener, result -> ai_addr, (int)result->ai_addrlen);
    if (bindRes == SOCKET_ERROR) {
        perror("Failed to bind!\n");
        return 1;
    }
    // Listen for connection
    SOCKET clientSocket = INVALID_SOCKET;
    bool serverRunning = true;
    while (serverRunning == true) {
        if(listen(listener, SOMAXCONN) == SOCKET_ERROR) {
            perror("Error on listening for a socket!\n");
            serverRunning = false;
        }
        // Accept client connection
        clientSocket = accept(listener, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            perror("Could not accept client!\n");
        } else {
            printf("Connection Accepted\n");
        }
        // TODO: use multithreading so can handle multiple requests simultaneously
        char* res = readSocket(&clientSocket);
        printf("Request: %s\n", res);
        free(res);
    }

    closesocket(clientSocket);
    closesocket(listener);
    freeaddrinfo(result);
    WSACleanup();
    return 0;
}
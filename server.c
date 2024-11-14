#include "server.h"

int main(int argc, char** argv) {
    if (argc != 1) {
        perror("Number of args inncorrect!\n");
        return 1;
    }
    char* port = argv[0];
    // TODO: check if port is valid
    // WSA Initialisation
    WSADATA wsaData;
    int winSockInitRes = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(winSockInitRes != 0) {
        perror("Failed to init winsock! \n");
        return 1;
    }
    // Creating Server Socket
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(struct addrinfo));
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
    SOCKET clientSocket;
    bool serverRunning = true;
    while (serverRunning == true) {
        if(listen(listener, SOMAXCONN) == SOCKET_ERROR) {
            perror("Error on listening for a socket!\n");
            serverRunning = false;
        }
        // TODO: Accept client connection
    }


    closesocket(listener);
    freeaddrinfo(result);
    WSACleanup();
    return 0;
}
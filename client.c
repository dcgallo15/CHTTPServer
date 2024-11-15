#include "server.h"

int main(int argc, char** argv) {
    if(argc < 3) {
        perror("Not enough args!");
    }
    char* port = argv[1];
    char* req = argv[2];
    printf("Port: %s, Req: %s\n", port, req);
    // WSA Init
    WSADATA wsaData;
    int winSockInitRes = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(winSockInitRes != 0) {
        perror("Failed to init winsock! \n");
        return 1;
    }
    struct addrinfo *result = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    int getInfoRes = getaddrinfo(NULL, port, &hints, &result);
    if (getInfoRes != 0) {
        printf("%d\n", getInfoRes);
        perror("getaddrinfo failed!\n");
        return 1;
    }
    SOCKET sock = INVALID_SOCKET;
    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    int connectRes = connect(sock, result->ai_addr, (int)result->ai_addrlen);
    if (connectRes == SOCKET_ERROR) {
        perror("Failed to connect!\n");
        sock = INVALID_SOCKET;
    } else {
        printf("Connnected!\n");
    }
    // Here will get file that req gives then send that over
    int sendRes = send(sock, req, (int)strlen(req), 0);
    if (sendRes == SOCKET_ERROR) {
        perror("Send Failed!\n");
    } else {
        printf("Request Written!%s\n", req);
    }
    // Shutdown connection
    int shutdownRes = shutdown(sock, SD_SEND);
    if (shutdownRes == SOCKET_ERROR) {
        perror("Error on socket shutdown!\n");
    }
    closesocket(sock);
    freeaddrinfo(result);
    WSACleanup();
    return 0;
}
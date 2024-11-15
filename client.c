#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library

int main(int argc, char** argv) {
    if(argc < 3) {
        perror("Not enough args!");
    }
    char* port = argv[1];
    char* req = argv[2];
    printf("Port: %s, Req: %s\n", port, req);
    return 0;
}
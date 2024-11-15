#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <Windef.h>
#include <windows.h>

// Ensures these work correctly
void WSAAPI freeaddrinfo( struct addrinfo* );
int WSAAPI getaddrinfo( const char*, const char*, const struct addrinfo*, struct addrinfo** );
int WSAAPI getnameinfo( const struct sockaddr*, socklen_t, char*, DWORD, char*, DWORD, int );

#pragma comment(lib, "Ws2_32.lib")

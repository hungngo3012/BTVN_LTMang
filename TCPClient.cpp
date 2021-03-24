// Client3.cpp : Tao client gui xau ky tu den server
//


#include <stdio.h>
#include <math.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    char add[10];
    printf("Dia chi server: ");
    gets_s(add, sizeof(add));
    addr.sin_addr.s_addr = inet_addr(add);
    char port[5];
    printf("Cong ket noi: ");
    gets_s(port, sizeof(port));
    int temp = atoi(port);
    addr.sin_port = htons(temp);

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Connect failed: %d\n", ret);
        return 1;
    }

    char buf[256];

    // Nhap du lieu tu ban phim va gui cho server
    while (1)
    {
        printf("Nhap xau ky tu: ");
        gets_s(buf, sizeof(buf));

        send(client, buf, strlen(buf), 0);

        if (strcmp(buf, "exit") == 0)
            break;
    }

    closesocket(client);
    WSACleanup();
}
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#define EXAMPLE_MACRO_NAME
#pragma warning(disable : 4996)
#pragma warning(suppress : 4996)
#pragma comment(lib, "ws2_32")


int main()
{
    typedef struct {
        char name[30];
        int logic_drive;
        int sectors;
        int bytes;
        int freeC;
        int totalC;
    }CPU;
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    char port[5];
    gets_s(port, sizeof(port));
    int temp = atoi(port);
    addr.sin_port = htons(temp);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);

    printf("Dang cho ket noi\n");
    SOCKET client = accept(listener, NULL, NULL);

    printf("Chap nhan ket noi: %d\n", client);
    int ret;
    CPU cpu;
    ret = recv(client, (char*)&cpu, sizeof(cpu), 0);
    printf("Ten CPU: ");
    printf("%s\n", cpu.name);
    printf("logic_driver: ");
    printf("%d\n", cpu.logic_drive);
    printf("So bytes: ");
    printf("%d\n", cpu.bytes);
    printf("Tong dung luong o C: ");
    printf("%d\n", cpu.totalC);
    printf("Tong dung luong o C con trong: ");
    printf("%d\n", cpu.freeC);
    printf("Sectors: ");
    printf("%d\n", cpu.sectors);

    closesocket(client);
    closesocket(listener);
    WSACleanup();
}
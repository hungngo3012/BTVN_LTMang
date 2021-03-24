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

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("Cong ket noi: ");
    char port[5];
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

    char name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(name) / sizeof(name[0]);
    GetComputerNameA(name, &size);
    //Kich thuoc Logical Driver
    char szLogicalDrives[MAX_PATH] = {};
    DWORD dwResult = GetLogicalDriveStringsA(MAX_PATH, szLogicalDrives);
    //Kich thuoc o dia
    unsigned long Sectors, Bytes, FreeC, TotalC;
    GetDiskFreeSpaceA("C:\\", &Sectors, &Bytes, &FreeC, &TotalC);


    CPU cpu;
    strcpy(cpu.name, name);
    cpu.sectors = Sectors;
    cpu.bytes = Bytes;
    cpu.freeC = FreeC;
    cpu.totalC = TotalC;

    send(client, (char*)&cpu, sizeof(cpu), 0);

    closesocket(client);
    WSACleanup();
}
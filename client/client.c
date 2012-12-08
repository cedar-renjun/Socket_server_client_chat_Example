
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 27015

WSADATA wsaData;
SOCKET ConnectSocket = INVALID_SOCKET;
char SendBuf[DEFAULT_BUFLEN];
char RecvBuf[DEFAULT_BUFLEN];
char IP[16];
struct sockaddr_in ServerCfg;
char WelcomeInfo[] = 
{    
"\t===============WIFI Shield Dirver================\r\n"
"\tName: TCP Socket Example\r\n"
"\tPORT : 27015\r\n"
"\t=============== CooCox Team =====================\r\n"
};

int main(void)
{
    int tmp = 0;
    int cnt = 0;
    int iResult = 0;

	printf(WelcomeInfo);
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\r\n", iResult);
        return 1;
    }
	printf("Initial WinSock OK\r\r\n");

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ConnectSocket  == INVALID_SOCKET) 
	{
        printf("socket failed with error: %ld\r\n", WSAGetLastError());        
        WSACleanup();
        return 1;
    }
	printf("Create Socket OK\r\n");
    
    //Connect to Server
    printf("Please Input Server IP:");
    scanf("%s", IP);
	getchar();
	ServerCfg.sin_family = AF_INET;
	ServerCfg.sin_port = htons(DEFAULT_PORT);
	ServerCfg.sin_addr.s_addr = inet_addr(IP);

    printf("Try to connect server\r\n");
    iResult = connect(ConnectSocket, (struct sockaddr *)&ServerCfg, sizeof(struct sockaddr));
    if (iResult == SOCKET_ERROR)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    printf("Connect to server!\r\n");
    printf("You can Send message Now!\r\n\r\n");
    // Send Message to Server
	while(1)
	{

        printf("-----------Sending Message---------\r\n");
		gets(SendBuf);

        iResult = send( ConnectSocket, SendBuf, strlen(SendBuf), 0 );
        if (iResult == SOCKET_ERROR) 
        {
            printf("send failed with error: %d\r\n", WSAGetLastError());
        }
        
        printf("-----------Getting Message---------\r\n");
        iResult = recv( ConnectSocket, RecvBuf, DEFAULT_BUFLEN, 0 );
        if (iResult < 0) 
        {
            printf("receive failed with error: %d\r\n", WSAGetLastError());
        }
        else if(iResult > 0)
        {
			puts(RecvBuf);
        }        
    }    
}

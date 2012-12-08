
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 27015

char RecvBuf[DEFAULT_BUFLEN];
char SendBuf[DEFAULT_BUFLEN];

struct sockaddr_in ServerCfg;
SOCKET ListenSocket = INVALID_SOCKET;
SOCKET ClientSocket = INVALID_SOCKET;  
char WelcomeInfo[] = 
{    
"\t===============WIFI Shield Dirver================\r\n"
"\tName: TCP Socket Example\r\n"
"\tPORT : 27015\r\n"
"\t=============== CooCox Team =====================\r\n"
};
int main(void)
{
    WSADATA wsaData;
    int iResult = 0;
	int iSendResult = 0;

    printf(WelcomeInfo);
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
	{
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }
	printf("Initial WinSock OK\r\n");

    // Create a SOCKET
    ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ListenSocket == INVALID_SOCKET) 
	{
        printf("socket failed with error: %ld\n", WSAGetLastError());        
        WSACleanup();
        return 1;
    }
	printf("Create Socket OK\r\n");

    // Setup the TCP listening socket
	ServerCfg.sin_family = AF_INET;
	ServerCfg.sin_port = htons(DEFAULT_PORT);
	ServerCfg.sin_addr.s_addr = htonl(INADDR_ANY);

    iResult = bind(ListenSocket,(struct sockaddr *)&ServerCfg, sizeof(struct sockaddr));
    if(iResult == SOCKET_ERROR)
	{
        printf("bind failed with error: %d\n", WSAGetLastError());        
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }    
	printf("Bind to PORT OK\r\n");

    
	// Begin listen PORT
    iResult = listen(ListenSocket, 5);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
	printf("Start Listen PORT\r\n");
	printf("Waitting Client ...\r\n");

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
	printf("Client Connect Now\r\n");

    // No longer need server socket
    closesocket(ListenSocket);

	printf("Everything is OK ,You Can Talk Now\r\n\r\n");    

	while(1)
	{		
		printf("-------------Getting Message-----------\r\n");
		iResult = recv(ClientSocket, RecvBuf, DEFAULT_BUFLEN, 0);
        if(iResult > 0)
		{           
			puts(RecvBuf);
		}
		else if(iResult < 0)
		{
			printf("Error! Can not get message\r\n");
		}
				
		printf("-------------Sending Message-----------\r\n");

		gets(SendBuf);
		iResult = send(ClientSocket, SendBuf, strlen(SendBuf), 0 );
		if (iResult == SOCKET_ERROR) 
		{
			printf("send failed with error: %d\r\n", WSAGetLastError());				
		}
	}    
}

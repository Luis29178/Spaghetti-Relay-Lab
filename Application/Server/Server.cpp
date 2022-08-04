#define _CRT_SECURE_NO_WARNINGS                 // turns of deprecated warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS			 // turns of deprecated warnings for winsock


#include "Server.h"
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")

SOCKET listenSocket;
SOCKET ComSocket;
int result = NULL;

int Server::init(uint16_t port)
{
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	result = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR)
	{		
		return BIND_ERROR;
	}

	result = listen(listenSocket, 1);
	if (result == SOCKET_ERROR)
	{
		return SETUP_ERROR;
	}

	ComSocket = accept(listenSocket, NULL, NULL); // Code will wait for a responce from a client here 
	if (ComSocket == INVALID_SOCKET)
	{
		return SETUP_ERROR;
	}

	return SUCCESS;
}
int Server::readMessage(char* buffer, int32_t size)
{
	
	result = reciveTcpData(ComSocket, (char*)buffer, size);
	if ((result == SOCKET_ERROR) || (result == 0))
	{
		// WSAGetLastError() retrives the error in witch result termintated with
		int error = WSAGetLastError();
		return MESSAGE_ERROR;

	}

	return SUCCESS;
}
int Server::sendMessage(char* data, int32_t length)
{
	memset(data, 0, length);
	strcpy(data, "I'm a message from the Server");

	result = sendTcpData(ComSocket, data, length);
	if ((result == SOCKET_ERROR) || (result == 0))
	{

		int error = WSAGetLastError();
		return MESSAGE_ERROR;

	}
	return SHUTDOWN;
}
void Server::stop()
{
	shutdown(listenSocket, SD_BOTH);
	closesocket(listenSocket);

	shutdown(ComSocket, SD_BOTH);
	closesocket(ComSocket);

}
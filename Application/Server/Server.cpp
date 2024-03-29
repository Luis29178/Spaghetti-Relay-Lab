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
		return CONNECT_ERROR;
	}

	return SUCCESS;
}
int Server::readMessage(char* buffer, int32_t size)
{

	int len = recv(ComSocket, buffer, size, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		return DISCONNECT;
	}
	if (len > size)
	{
		return PARAMETER_ERROR;
	}

	result = reciveTcpData(ComSocket, (char*)buffer, len);
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
	int len = send(ComSocket, (const char*)data, length, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		return DISCONNECT;
	}
	if (len < 0 || len >255)
	{
		return PARAMETER_ERROR;
	}

	result = sendTcpData(ComSocket, data, len);
	if ((result == SOCKET_ERROR) || (result == 0))
	{

		int error = WSAGetLastError();
		return MESSAGE_ERROR;

	}
	return SUCCESS;
}
void Server::stop()
{
	shutdown(listenSocket, SD_BOTH);
	closesocket(listenSocket);

	shutdown(ComSocket, SD_BOTH);
	closesocket(ComSocket);

}
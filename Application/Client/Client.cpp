#define _CRT_SECURE_NO_WARNINGS                 // turns of deprecated warnings
#define _WINSOCK_DEPRECATED_NO_WARNINGS			 // turns of deprecated warnings for winsock


#include "Client.h"
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")



SOCKET ComSocket;
int result;
int Client::init(uint16_t port, char* address)
{
	ComSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ComSocket == INVALID_SOCKET)
	{
		
		return SETUP_ERROR;
	}
	sockaddr_in serverAddr; 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = inet_addr(address);
	serverAddr.sin_port = htons(port);

	int result = connect(ComSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (result == SOCKET_ERROR)
	{
		
		return CONNECT_ERROR;
	}


	return SUCCESS;
}
int Client::readMessage(char* buffer, int32_t size)
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
int Client::sendMessage(char* data, int32_t length)
{
	memset(data, 0, length);
	strcpy(data, "I'm a message from the client");

	result = sendTcpData(ComSocket, data, length);
	if ((result == SOCKET_ERROR) || (result == 0))
	{

		int error = WSAGetLastError();
		return MESSAGE_ERROR;

	}

	return SUCCESS;
}
void Client::stop()
{
	shutdown(ComSocket, SD_BOTH);
	closesocket(ComSocket);
}
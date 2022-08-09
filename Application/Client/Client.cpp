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

	
	 int len = recv(ComSocket, buffer , size, 0);
	 if ((len == SOCKET_ERROR) || (len == 0))
	 {
		 return MESSAGE_ERROR;
	 }
	
	result = reciveTcpData(ComSocket, (char*)buffer,len);
	if ((result == SOCKET_ERROR) || (result == 0))
	{
		return MESSAGE_ERROR;
	}

	return SUCCESS;
}
int Client::sendMessage(char* data, int32_t length)
{
	
	int len = send(ComSocket, (const char*)data, length, 0);
	if ((len == SOCKET_ERROR) || (len == 0))
	{
		return MESSAGE_ERROR;
	}



	result = sendTcpData(ComSocket, data, len);
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
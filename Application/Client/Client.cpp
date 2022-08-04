#include "Client.h"




SOCKET ComSocket;

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
	return SHUTDOWN;
}
int Client::sendMessage(char* data, int32_t length)
{
	return SHUTDOWN;
}
void Client::stop()
{

}
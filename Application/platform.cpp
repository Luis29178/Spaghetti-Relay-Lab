#include "platform.h"

int sendTcpData(SOCKET skSocket, const char *data, uint16_t length)
{
	int result;
	int bytesSent = 0;

	

	while (bytesSent < length)
	{

		

		result = send(skSocket, (const char *) data + bytesSent, length - bytesSent, 0);

		if (result <= 0)
			return result;

		bytesSent += result;
	}

	return bytesSent;
}

int reciveTcpData(SOCKET s, char* buffer, int length)
{
	int total = 0;



	do
	{
		
		int ret = recv(s, buffer + total, length - total, 0);
		if (ret < 1)
			return ret;
		else
			total += ret;

	} while (total < length);

	return total;
}

// printerstatus.cpp

#include <windows.h>
#include <stdio.h>
#pragma comment(linker, "/defaultlib:ws2_32.lib")

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: printerstatus [ip address] [message]\n");
		return 1;
	}

	WSADATA wsa;
	WSAStartup(0x0202, &wsa);

	unsigned long addr = inet_addr(argv[1]);
	if (addr == INADDR_NONE || addr == INADDR_ANY)
	{
		printf("\"%s\" is not a valid IP address", argv[1]);
		return 2;
	}

	sockaddr_in sin_addr;
	sin_addr.sin_family = AF_INET;
	sin_addr.sin_port = htons(9100);
	sin_addr.sin_addr.S_un.S_addr = addr;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		printf("\"%s\": Unable to open socket\n", argv[1]);
		return 3;
	}

	if (connect(s, (sockaddr*)&sin_addr, sizeof(sin_addr)) == SOCKET_ERROR)
	{
		printf("\"%s\": Unable to connect\n", argv[1]);
		return 4;
	}

	char msg[256];
	sprintf_s(msg, "\x1B%%-12345X@PJL JOB\n@PJL RDYMSG DISPLAY=\"%s\"\n@PJL EOJ\n\x1B%%-12345X\n", argv[2]);
	if (send(s, msg, strlen(msg), 0) == SOCKET_ERROR)
	{
		printf("\"%s\": Unable to send\n", argv[1]);
		return 5;
	}

	closesocket(s);
	WSACleanup();

	printf("\"%s\": \"%s\"\n", argv[1], argv[2]);
	return 0;
}

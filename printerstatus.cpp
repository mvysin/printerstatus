// printerstatus.cpp
// PJL printer ready-message changer, for office pranks and more!
// Copyright (C) 2011, Michael Vysin
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(linker, "/defaultlib:ws2_32.lib")

static SOCKET getSocket(const char *hostname, const char *port)
{
    // resolve IP or hostname to IPv4 or IPv6 socket
	addrinfo hint, *addrs;
	memset(&hint, 0, sizeof(addrinfo));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(hostname, port, &hint, &addrs))
        return INVALID_SOCKET;

    // try each address until success
    SOCKET s = INVALID_SOCKET;
    for (addrinfo *curaddr = addrs; curaddr; curaddr = curaddr->ai_next)
    {
        s = socket(curaddr->ai_family, curaddr->ai_socktype, curaddr->ai_protocol);
        if (s == INVALID_SOCKET)
            continue;

        // stop when connect succeeds
        if (!connect(s, curaddr->ai_addr, (int)curaddr->ai_addrlen))
            break;

        closesocket(s);
        s = INVALID_SOCKET;
    }

    freeaddrinfo(addrs);

    return s;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
        printf("PrinterStatus (c) 2011 Michael Vysin\n"
               "This program comes with ABSOLUTELY NO WARRANTY; for details see the file LICENSE.\n"
               "This is free software, and you are welcome to redistribute it under the terms\n"
               "of the GNU General Public License v2.0 or later.\n"
               "\n"
		       "Usage: printerstatus [ip address or hostname] [message]\n");
		return 1;
	}


    // create the message:
    // <ESC>%-12345X
    // @PJL JOB
    // @PJL RDYMSG DISPLAY="INSERT COIN"
    // @PJL EOJ
    // <ESC>%-12345X
    //
	char msg[512];
	if (sprintf_s(msg, "\x1B%%-12345X@PJL JOB\n@PJL RDYMSG DISPLAY=\"%s\"\n@PJL EOJ\n\x1B%%-12345X\n", argv[2]) == -1)
    {
        printf("Message too long\n");
        return 3;
    }


	WSADATA wsa;
	WSAStartup(0x0202, &wsa);

    SOCKET s = getSocket(argv[1], "9100");
	if (s == INVALID_SOCKET)
	{
		printf("\"%s\": Unable to connect to job submission port\n", argv[1]);
		return 2;
	}

	if (send(s, msg, (int)strlen(msg), 0) == SOCKET_ERROR)
	{
		printf("\"%s\": Unable to send\n", argv[1]);
		return 4;
	}

    shutdown(s, SD_SEND);
	closesocket(s);

	WSACleanup();


	printf("\"%s\": \"%s\"\n", argv[1], argv[2]);
	return 0;
}

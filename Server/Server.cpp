#include "Common.h"
#include "GameRoom.h"

#define SERVERPORT 9000
#define MAX_CLIENTS 2

// Ŭ���̾�Ʈ�� ó���ϴ� ������
DWORD WINAPI ProcessClient1(LPVOID arg) 
{

}

DWORD WINAPI ProcessClient2(LPVOID arg)
{

}

int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;
	int ClientNum = 0;

	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}
		ClientNum++;

		// Ŭ��� �� ���� �Ǿ����� ��� 
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// Ŭ���̾�Ʈ ó�� ��� ������ ����
		if (ClientNum == 1) {
			hThread = CreateThread(NULL, 0, ProcessClient1, (LPVOID)client_sock, 0, NULL);
		}
		else if (ClientNum == MAX_CLIENTS) {
			hThread = CreateThread(NULL, 0, ProcessClient2, (LPVOID)client_sock, 0, NULL);
		}
		
		if (hThread == NULL) { 
			closesocket(client_sock); 
		}
		else { 
			CloseHandle(hThread); 
		}

		// ������� �ο��� 2���ΰ�?
		// no->�ݺ�, yes -> �� ó�� ������ ����
		if (ClientNum == MAX_CLIENTS) {
			hThread = CreateThread(NULL, 0, ProcessClient1, NULL, 0, NULL);

			// ���̻� ���� ���� ����
			break;
		}
	}

	// ���� ����
	WSACleanup();
	return 0;
}

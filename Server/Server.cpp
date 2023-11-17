#include "Common.h"
#include "GameRoom.h"

#define SERVERPORT 9000
#define MAX_CLIENTS 2
#define MAX_ROOMS 20

using std::array;

HANDLE hClient1Event;
HANDLE hClient2Event;
HANDLE hRoomEvent;

// Ŭ���̾�Ʈ�� ó���ϴ� ������
DWORD WINAPI ProcessClient1(LPVOID arg) 
{
	SOCKET client_sock = (SOCKET)arg;
	DWORD retval;
	retval = WaitForSingleObject(hClient1Event, INFINITE);

	// Ŭ���̾�Ʈ ó�� ����




	SetEvent(hClient2Event);
}

DWORD WINAPI ProcessClient2(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	DWORD retval;
	retval = WaitForSingleObject(hClient2Event, INFINITE);

	// Ŭ���̾�Ʈ ó�� ����




	SetEvent(hRoomEvent);
}

DWORD WINAPI ProcessRoom(LPVOID arg)
{
	DWORD retval;
	retval = WaitForSingleObject(hRoomEvent, INFINITE);

	// �뾲���� ó�� ����




	SetEvent(hClient1Event);
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
	int RoomNum = 0;
	SOCKET client_sockets[MAX_CLIENTS];

	HANDLE hClientArrToMakeRoom[2];
	array<HANDLE, MAX_ROOMS> hRoomArr;

	while (1) {

		// ������ ��� ���� �̺�Ʈ
		hClient1Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hClient2Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hRoomEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		//TODO: ���� �� á�� �� �ƿ� �� �ް� �Ұ��� �ް��� �ȳ��� �Ұ���
		

		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}


		client_sockets [ClientNum++] = client_sock;

		// Ŭ��� �� ���� �Ǿ����� ��� 
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// Ŭ���̾�Ʈ ó�� ��� ������ ����
		if (ClientNum < MAX_CLIENTS) {
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

		hClientArrToMakeRoom[ClientNum - 1] = hThread;

		// ������� �ο��� 2���ΰ�?
		// no->�ݺ�, yes -> �� ó�� ������ ����
		if (ClientNum == MAX_CLIENTS) {
			hThread = CreateThread(NULL, 0, ProcessClient1, hClientArrToMakeRoom, 0, NULL);

			// �غ� �Ϸ� �޽��� ������
			for (int i = 0; i < MAX_CLIENTS; ++i) {
				char buffer[100];
				sprintf(buffer, "Game is ready for Client %d.", ClientNum);
				send(client_sockets[i], buffer, strlen(buffer), 0);
			}

			// Ŭ��1 ��ȣ on
			SetEvent(hClient1Event);

			// ���̻� ���� ���� ����
			break;
		}
		else
		{

		}
	}

	CloseHandle(hClient1Event);
	CloseHandle(hClient2Event);
	CloseHandle(hRoomEvent);

	// ���� ����
	WSACleanup();
	return 0;
}

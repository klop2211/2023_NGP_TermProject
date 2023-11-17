#include "Common.h"
#include "GameRoom.h"

#define SERVERPORT 9000
#define MAX_CLIENTS 2
#define MAX_ROOMS 20

using std::array;

HANDLE hClient1Event;
HANDLE hClient2Event;
HANDLE hRoomEvent;

// 클라이언트를 처리하는 쓰레드
DWORD WINAPI ProcessClient1(LPVOID arg) 
{
	SOCKET client_sock = (SOCKET)arg;
	DWORD retval;
	retval = WaitForSingleObject(hClient1Event, INFINITE);

	// 클라이언트 처리 로직




	SetEvent(hClient2Event);
}

DWORD WINAPI ProcessClient2(LPVOID arg)
{
	SOCKET client_sock = (SOCKET)arg;
	DWORD retval;
	retval = WaitForSingleObject(hClient2Event, INFINITE);

	// 클라이언트 처리 로직




	SetEvent(hRoomEvent);
}

DWORD WINAPI ProcessRoom(LPVOID arg)
{
	DWORD retval;
	retval = WaitForSingleObject(hRoomEvent, INFINITE);

	// 룸쓰레드 처리 로직




	SetEvent(hClient1Event);
}

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
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

		// 쓰레드 제어를 위한 이벤트
		hClient1Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hClient2Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hRoomEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		//TODO: 방이 다 찼을 때 아예 안 받게 할건지 받고나서 안내를 할건지
		

		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}


		client_sockets [ClientNum++] = client_sock;

		// 클라랑 잘 연결 되었는지 출력 
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		// 클라이언트 처리 담당 스레드 생성
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

		// 대기중인 인원이 2명인가?
		// no->반복, yes -> 방 처리 스레드 생성
		if (ClientNum == MAX_CLIENTS) {
			hThread = CreateThread(NULL, 0, ProcessClient1, hClientArrToMakeRoom, 0, NULL);

			// 준비 완료 메시지 보내기
			for (int i = 0; i < MAX_CLIENTS; ++i) {
				char buffer[100];
				sprintf(buffer, "Game is ready for Client %d.", ClientNum);
				send(client_sockets[i], buffer, strlen(buffer), 0);
			}

			// 클라1 신호 on
			SetEvent(hClient1Event);

			// 더이상 접속 받지 않음
			break;
		}
		else
		{

		}
	}

	CloseHandle(hClient1Event);
	CloseHandle(hClient2Event);
	CloseHandle(hRoomEvent);

	// 윈속 종료
	WSACleanup();
	return 0;
}

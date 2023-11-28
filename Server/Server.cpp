#define _CRT_SECURE_NO_WARNINGS
#include <queue>
#include "Common.h"
#include "GameRoom.h"
#include "StateMessage.h"
#include "MsgInstence.h"

// 최대 방 개수만큼 이벤트 생성
array<Events, MAX_ROOMS> events;

// 최대 방 개수만큼 소켓 보유
SOCKET client_sockets[MAX_CLIENTS];

// 상태 메세지를 저장할 공유 버퍼
array<array<StateMsgInfo, MAX_CLIENTS>, MAX_ROOMS> SharedBuffer;

void ProcessStateMsg(BYTE StateMsg)
{
	switch (StateMsg)
	{
	default:
		break;
	}
}

//struct StateMsgBuffer {
//	BYTE stateMsg;
//};

int GetStateMsgType(BYTE LowerBits)
{
	switch (LowerBits)
	{
	case (int)StateMsgType::MonsterSpawn:	return sizeof(MonsterSpawnStateMsg);
	case (int)StateMsgType::MonsterHp:		return sizeof(MonsterHpStateMsg);
	case  (int)StateMsgType::PlayerMove:	return sizeof(PlayerMoveStateMsg);
	case (int)StateMsgType::UseCard:		return sizeof(UseCardStateMsg);
	case  (int)StateMsgType::CastleHp:		return sizeof(CastleHpStateMsg);
	default:
		printf("State Message Type에 오류");
		return 0;
	}
}

// 클라이언트를 처리하는 쓰레드
DWORD WINAPI ProcessClient1(LPVOID arg) 
{
	ClientArg* Arg = (ClientArg*)arg;
	SOCKET client_sock = Arg->sock;
	int RoomNum = Arg->RoomNumber;

	DWORD retval;
	retval = WaitForSingleObject(events[RoomNum].hClient1Event, INFINITE);

	// 클라이언트 처리 로직

	// 상태 메시지 수신
	BYTE StateMsg;
	BYTE upper2Bits = 0;
	BYTE lower6Bits = 0;
	StateMsgArgu* StateMsgArg = nullptr;

	int ReceiveStateMsg = recv(client_sockets[Client1], (char*)&StateMsg, sizeof(BYTE), 0);
	if (ReceiveStateMsg == SOCKET_ERROR) {
		err_quit("ReceiveStateMsg Err");
	}
	else {
		// 상위 2비트 추출
		upper2Bits = ReceiveStateMsg >> 6;

		// 하위 6비트 추출
		lower6Bits = ReceiveStateMsg & 0x3F;

		// 추가로 읽을 바이트 사이즈
		int MsgSize = GetStateMsgType(lower6Bits);

		// 추가로 받을 인수 동적할당
		StateMsgArg = MsgInstence::GetStateMsgArguType(lower6Bits);

		ReceiveStateMsg = recv(client_sockets[Client1], (char*)StateMsgArg, MsgSize, 0);
	}

	// 하위 6비트를 통해 게임오버 판별
	//StateMsg 구체화되면 수정 예정
	ProcessStateMsg(lower6Bits);
	
	// 받은 내용 그대로 공유 버퍼에 쓰기
	SharedBuffer[RoomNum][0].StateMsg = StateMsg;
	SharedBuffer[RoomNum][0].pStateMsgArgu = StateMsgArg;

	SetEvent(events[RoomNum].hClient2Event);
	return NULL;
}

DWORD WINAPI ProcessClient2(LPVOID arg)
{
	ClientArg* Arg = (ClientArg*)arg;
	SOCKET client_sock = Arg->sock;
	int RoomNum = Arg->RoomNumber;

	DWORD retval;
	retval = WaitForSingleObject(events[RoomNum].hClient2Event, INFINITE);

	// 클라이언트 처리 로직

	// 상태 메시지 수신
	BYTE StateMsg;
	BYTE upper2Bits = 0;
	BYTE lower6Bits = 0;
	StateMsgArgu * StateMsgArg = nullptr;

	int ReceiveStateMsg = recv(client_sockets[Client2], (char*)&StateMsg, sizeof(BYTE), 0);
	if (ReceiveStateMsg == SOCKET_ERROR) {
		err_quit("ReceiveStateMsg Err");
	}
	else {
		// 상위 2비트 추출
		upper2Bits = ReceiveStateMsg >> 6;

		// 하위 6비트 추출
		lower6Bits = ReceiveStateMsg & 0x3F;

		// 추가로 읽을 바이트 사이즈
		int MsgSize = GetStateMsgType(lower6Bits);

		// 추가로 받을 인수 동적할당
		StateMsgArg = MsgInstence::GetStateMsgArguType(lower6Bits);

		ReceiveStateMsg = recv(client_sockets[Client1], (char*)StateMsgArg, MsgSize, 0);
	}

	// 하위 6비트를 통해 게임오버 판별
	ProcessStateMsg(lower6Bits);

	SharedBuffer[RoomNum][1].StateMsg = StateMsg;
	SharedBuffer[RoomNum][1].pStateMsgArgu = StateMsgArg;

	SetEvent(events[RoomNum].hRoomEvent);
	return NULL;
}

DWORD WINAPI ProcessRoom(LPVOID arg)
{
	DWORD retval;
	RoomArg* Arg = (RoomArg*)arg;
	int RoomNum = Arg->RoomNumber;
	array<HANDLE, MAX_CLIENTS> hClients;

	// Array는 Vector와 다르게 Move의 효율이 좋지 않다.
	//TODO: 실행되는지 확인
	memcpy(hClients.data(), Arg->Client.data(), sizeof(HANDLE) * MAX_CLIENTS);

	GameRoom* pGameRoom = new GameRoom;
	// Main Game Room 로직
	while (true)
	{
		retval = WaitForSingleObject(events[RoomNum].hRoomEvent, INFINITE);

		pGameRoom->Update(SharedBuffer[RoomNum]);

		SetEvent(events[RoomNum].hClient1Event);
	}
	delete pGameRoom;
	return NULL;
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
	HANDLE hThread = nullptr;
	int ClientNum = 0;
	int RoomNum = 0;
	

	array<HANDLE, MAX_ROOMS> hClientArrToMakeRoom;
	array<HANDLE, MAX_ROOMS> hRoomArr;

	while (1) {
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
		ClientArg clientarg;
		clientarg.RoomNumber = RoomNum;
		clientarg.sock = client_sock;
		if (ClientNum < MAX_CLIENTS) {
			hThread = CreateThread(NULL, 0, ProcessClient1, (LPVOID)&clientarg, 0, NULL);
		}
		else if (ClientNum == MAX_CLIENTS) {
			hThread = CreateThread(NULL, 0, ProcessClient2, (LPVOID)&clientarg, 0, NULL);

		}
		
		if (hThread == NULL) { 
			closesocket(client_sock); 
		}
		else { 
			CloseHandle(hThread); 
		}

		hClientArrToMakeRoom[ClientNum] = hThread;

		// 대기중인 인원이 2명인가?
		// no->반복, yes -> 방 처리 스레드 생성
		if (ClientNum == MAX_CLIENTS) {
			RoomArg arg;

			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				arg.Client[i] = hClientArrToMakeRoom[i];
			}
			arg.RoomNumber = RoomNum;
			hThread = CreateThread(NULL, 0, ProcessRoom, &arg, 0, NULL);

			// 준비 완료 메시지 보내기
			for (int i = 0; i < MAX_CLIENTS; ++i) {
				char buffer[100];
				sprintf(buffer, "Game is ready for Client %d.", ClientNum);
				send(client_sockets[i], buffer, strlen(buffer), 0);
			}

			// 클라1 신호 on
			SetEvent(events[RoomNum++].hClient1Event);

			// 더이상 접속 받지 않음
			break;
		}
		else
		{

		}
	}

	//for (auto& handle : events)
	//{
	//	CloseHandle(handle.hClient1Event);
	//	CloseHandle(handle.hClient2Event);
	//	CloseHandle(handle.hRoomEvent);
	//}

	// 윈속 종료
	WSACleanup();
	return 0;
}

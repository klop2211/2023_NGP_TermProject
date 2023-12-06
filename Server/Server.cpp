#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"
#include "GameRoom.h"
#include "StateMessage.h"
#include "MemoryReadStream.h"
#include "MemoryWriteStream.h"

// 최대 방 개수만큼 이벤트 생성
array<Events, MAX_ROOMS> events;

// 최대 방 개수만큼 소켓 보유
array<SOCKET, MAX_CLIENTS> client_sockets;

// 상태 메세지를 저장할 공유 버퍼
array<array<queue<StateMsgInfo>, MAX_CLIENTS>, MAX_ROOMS> SharedBuffer;

array<MemoryReadStream*, MAX_ROOMS> ReadStreamArr;

MemoryWriteStream* m_pStream;
void GameOver(array<array<WORD, (int)MonsterType::END>, MAX_CLIENTS> KillCntArr)
{
	GameOverMsg GOM;
	GOM.KillScore = KillCntArr;

	m_pStream = new MemoryWriteStream(client_sockets);
	m_pStream->Write(StateMsgType::GameOver);
	m_pStream->Write(GOM);
	m_pStream->Send();
}

bool IsGameOver(BYTE StateMsg, StateMsgArgu* arg)
{
	switch (StateMsg)
	{
	// 하위 6비트가 castleHp를 가리킬때 
	case (int)StateMsgType::CastleHp:
	{

		CastleHpStateMsg* Castle = static_cast<CastleHpStateMsg*>(arg);
		if (Castle->Hp <= 0)
		{
			//game over 
			for (int i = 0; i < MAX_CLIENTS; ++i) {
				char buffer[100];
				sprintf(buffer, "Game Over");
				send(client_sockets[i], buffer, strlen(buffer), 0);
			}
			return true;
		}
		else
			return false;
	}
		break;
	default:
		return false;
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
	case (int)StateMsgType::MonsterLocation:	return sizeof(MonsterLocationMsg);
	case (int)StateMsgType::MonsterHp:		return sizeof(MonsterHpMsg);
	case  (int)StateMsgType::PlayerLocation:return sizeof(PlayerLocationMsg);
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

	while (true)
	{
		retval = WaitForSingleObject(events[RoomNum].hClient1Event, INFINITE);
		//printf("hClient1Event Run\n");

		// 클라이언트 처리 로직
		bool bIsGameOver = false;
		ReadStreamArr[RoomNum]->Read(client_sock, SharedBuffer[RoomNum][0], bIsGameOver);
		if (bIsGameOver)
		{
			CloseHandle(GetCurrentThread());
		}
		else
		{
			SetEvent(events[RoomNum].hClient2Event);
		}
	}
	
	return NULL;
}

DWORD WINAPI ProcessClient2(LPVOID arg)
{
	ClientArg* Arg = (ClientArg*)arg;
	SOCKET client_sock = Arg->sock;
	int RoomNum = Arg->RoomNumber;

	DWORD retval;
	while (true)
	{
		retval = WaitForSingleObject(events[RoomNum].hClient2Event, INFINITE);
		//printf("hClient2Event Run\n");

		// 클라이언트 처리 로직
		bool bIsGameOver = false;
		ReadStreamArr[RoomNum]->Read(client_sock, SharedBuffer[RoomNum][1], bIsGameOver);

		if (bIsGameOver)
		{
			CloseHandle(GetCurrentThread());
		}
		else
		{
			SetEvent(events[RoomNum].hRoomEvent);
		}
	}
		
	return NULL;
}

DWORD WINAPI ProcessRoom(LPVOID arg)
{
	DWORD retval;
	RoomArg* Arg = (RoomArg*)arg;
	int RoomNum = Arg->RoomNumber;
	array<HANDLE, MAX_CLIENTS> hClients;

	GameRoom* pGameRoom = new GameRoom(Arg->Clients);
	// Main Game Room 로직
	while (!pGameRoom->GetIsOver())
	{
		retval = WaitForSingleObject(events[RoomNum].hRoomEvent, INFINITE);
		//printf("server Run\n");

		pGameRoom->Update(SharedBuffer[RoomNum]);

		//GameOver(pGameRoom->GetKillCount());
		SetEvent(events[RoomNum].hClient1Event);
	}


	// TODO: 적당한 위치로 옮기기
	//delete ReadStreamArr[RoomNum];
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
				arg.Clients[i] = client_sockets[i];
			}
			arg.RoomNumber = RoomNum;
			hThread = CreateThread(NULL, 0, ProcessRoom, &arg, 0, NULL);

			ReadStreamArr[RoomNum] = new MemoryReadStream();

			// 준비 완료 메시지 보내기
			//for (int i = 0; i < MAX_CLIENTS; ++i) {
			//	char buffer[100];
			//	sprintf(buffer, "Game is ready for Client %d.", ClientNum);
			//	send(client_sockets[i], buffer, strlen(buffer), 0);
			//}

			int i{ 0 };
			for (const auto& s : client_sockets)
			{
				StateMsgType SMT = StateMsgType::GameStart;
				retval = send(s, (char*)&SMT, sizeof(StateMsgType), 0);
				if (retval == SOCKET_ERROR) {
					err_display("send()");
				}
				retval = send(s, (char*)&i, sizeof(int), 0);
				if (retval == SOCKET_ERROR) {
					err_display("send()");
				}
				i++;
			}

			//{
			//	GameRoom* pGameRoom = new GameRoom(arg.Clients);
			//	while (true)
			//	{
			//		pGameRoom->Update(SharedBuffer[0]);
			//		pGameRoom->WriteMonsterState(MonsterType::Wolf, 0, MonsterStateType::Attack);
			//	}
			//}

			// 클라1 신호 on
			SetEvent(events[RoomNum++].hClient1Event);

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

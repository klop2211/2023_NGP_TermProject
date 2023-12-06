#define _CRT_SECURE_NO_WARNINGS
#include "Common.h"
#include "GameRoom.h"
#include "StateMessage.h"
#include "MemoryReadStream.h"
#include "MemoryWriteStream.h"

// �ִ� �� ������ŭ �̺�Ʈ ����
array<Events, MAX_ROOMS> events;

// �ִ� �� ������ŭ ���� ����
array<SOCKET, MAX_CLIENTS> client_sockets;

// ���� �޼����� ������ ���� ����
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
	// ���� 6��Ʈ�� castleHp�� ����ų�� 
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
		printf("State Message Type�� ����");
		return 0;
	}
}

// Ŭ���̾�Ʈ�� ó���ϴ� ������
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

		// Ŭ���̾�Ʈ ó�� ����
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

		// Ŭ���̾�Ʈ ó�� ����
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
	// Main Game Room ����
	while (!pGameRoom->GetIsOver())
	{
		retval = WaitForSingleObject(events[RoomNum].hRoomEvent, INFINITE);
		//printf("server Run\n");

		pGameRoom->Update(SharedBuffer[RoomNum]);

		//GameOver(pGameRoom->GetKillCount());
		SetEvent(events[RoomNum].hClient1Event);
	}


	// TODO: ������ ��ġ�� �ű��
	//delete ReadStreamArr[RoomNum];
	delete pGameRoom;
	return NULL;
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
	HANDLE hThread = nullptr;
	int ClientNum = 0;
	int RoomNum = 0;
	

	array<HANDLE, MAX_ROOMS> hClientArrToMakeRoom;
	array<HANDLE, MAX_ROOMS> hRoomArr;

	while (1) {
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

		// ������� �ο��� 2���ΰ�?
		// no->�ݺ�, yes -> �� ó�� ������ ����
		if (ClientNum == MAX_CLIENTS) {

			RoomArg arg;

			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				arg.Clients[i] = client_sockets[i];
			}
			arg.RoomNumber = RoomNum;
			hThread = CreateThread(NULL, 0, ProcessRoom, &arg, 0, NULL);

			ReadStreamArr[RoomNum] = new MemoryReadStream();

			// �غ� �Ϸ� �޽��� ������
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

			// Ŭ��1 ��ȣ on
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

	// ���� ����
	WSACleanup();
	return 0;
}

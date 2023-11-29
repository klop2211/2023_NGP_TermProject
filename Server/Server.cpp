#define _CRT_SECURE_NO_WARNINGS
#include <queue>
#include "Common.h"
#include "GameRoom.h"
#include "StateMessage.h"
#include "MsgInstence.h"

// �ִ� �� ������ŭ �̺�Ʈ ����
array<Events, MAX_ROOMS> events;

// �ִ� �� ������ŭ ���� ����
SOCKET client_sockets[MAX_CLIENTS];

// ���� �޼����� ������ ���� ����
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
	retval = WaitForSingleObject(events[RoomNum].hClient1Event, INFINITE);

	// Ŭ���̾�Ʈ ó�� ����

	// ���� �޽��� ����
	BYTE StateMsg;
	BYTE upper2Bits = 0;
	BYTE lower6Bits = 0;
	StateMsgArgu* StateMsgArg = nullptr;

	int ReceiveStateMsg = recv(client_sockets[Client1], (char*)&StateMsg, sizeof(BYTE), 0);
	if (ReceiveStateMsg == SOCKET_ERROR) {
		err_quit("ReceiveStateMsg Err");
	}
	else {
		// ���� 2��Ʈ ����
		upper2Bits = ReceiveStateMsg >> 6;

		// ���� 6��Ʈ ����
		lower6Bits = ReceiveStateMsg & 0x3F;

		// �߰��� ���� ����Ʈ ������
		int MsgSize = GetStateMsgType(lower6Bits);

		//Ŭ�󿡼� �ֱ������� ���� �޽��� ������
		//���� �޽����� ������ 0�� ������
		//���¸޽����� 0�ϋ��� StateMsgArg ���Ź��� �ʱ� & Ŭ�󿡼� �������� �ʱ�

		// ���¸޽����� 0�� �ƴ� ��
		//0�� ���� StateMsgArg == nullptr �״��
		if (ReceiveStateMsg != StateMsgNone)
		{
			// �߰��� ���� �μ� �����Ҵ�
			// TODO: ������ ������ �����ϰų� ����Ʈ ������ ����ؾ���
			StateMsgArg = MsgInstence::GetStateMsgArguType(lower6Bits);
			ReceiveStateMsg = recv(client_sockets[Client1], (char*)StateMsgArg, MsgSize, 0);
			if (ReceiveStateMsg == SOCKET_ERROR) {
				err_quit("ReceiveStateMsgArg Err");
			}
		}
	}

	// ���� 6��Ʈ�� ���� ���ӿ��� �Ǻ�
	//StateMsg ��üȭ�Ǹ� ���� ����
	ProcessStateMsg(lower6Bits);
	
	// ���� ���� �״�� ���� ���ۿ� ����
	SharedBuffer[RoomNum][0].StateMsg = StateMsg;
	SharedBuffer[RoomNum][0].pStateMsgArgu = StateMsgArg;
	
	// ������ ���ŵ� �����ʹ� ���� ������
	Arg->RoomNumber++;
	
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

	// Ŭ���̾�Ʈ ó�� ����

	// ���� �޽��� ����
	BYTE StateMsg;
	BYTE upper2Bits = 0;
	BYTE lower6Bits = 0;
	StateMsgArgu * StateMsgArg = nullptr;

	int ReceiveStateMsg = recv(client_sockets[Client2], (char*)&StateMsg, sizeof(BYTE), 0);
	if (ReceiveStateMsg == SOCKET_ERROR) {
		err_quit("ReceiveStateMsg Err");
	}
	else {
		// ���� 2��Ʈ ����
		upper2Bits = ReceiveStateMsg >> 6;

		// ���� 6��Ʈ ����
		lower6Bits = ReceiveStateMsg & 0x3F;

		// �߰��� ���� ����Ʈ ������
		int MsgSize = GetStateMsgType(lower6Bits);

		// ���¸޽����� 0�� �ƴ� ��
		//0�� ���� StateMsgArg == nullptr �״��
		if (ReceiveStateMsg != StateMsgNone)
		{
			// �߰��� ���� �μ� �����Ҵ�
			// TODO: ������ ������ �����ϰų� ����Ʈ ������ ����ؾ���
			StateMsgArg = MsgInstence::GetStateMsgArguType(lower6Bits);
			ReceiveStateMsg = recv(client_sockets[Client2], (char*)StateMsgArg, MsgSize, 0);
			if (ReceiveStateMsg == SOCKET_ERROR) {
				err_quit("ReceiveStateMsgArg Err");
			}
		}
	}

	// ���� 6��Ʈ�� ���� ���ӿ��� �Ǻ�
	ProcessStateMsg(lower6Bits);

	SharedBuffer[RoomNum][1].StateMsg = StateMsg;
	SharedBuffer[RoomNum][1].pStateMsgArgu = StateMsgArg;

	// ������ ���ŵ� �����ʹ� ���� ������
	Arg->RoomNumber++;

	SetEvent(events[RoomNum].hRoomEvent);
	return NULL;
}

DWORD WINAPI ProcessRoom(LPVOID arg)
{
	DWORD retval;
	RoomArg* Arg = (RoomArg*)arg;
	int RoomNum = Arg->RoomNumber;
	array<HANDLE, MAX_CLIENTS> hClients;

	// Array�� Vector�� �ٸ��� Move�� ȿ���� ���� �ʴ�.
	//TODO: ����Ǵ��� Ȯ��
	memcpy(hClients.data(), Arg->Client.data(), sizeof(HANDLE) * MAX_CLIENTS);

	GameRoom* pGameRoom = new GameRoom;
	// Main Game Room ����
	while (true)
	{
		retval = WaitForSingleObject(events[RoomNum].hRoomEvent, INFINITE);

		pGameRoom->Update(SharedBuffer[RoomNum]);
		
		// ���� ������Ʈ�� ���� �濡�� 
		Arg->RoomNumber++;

		SetEvent(events[RoomNum].hClient1Event);
	}
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
				arg.Client[i] = hClientArrToMakeRoom[i];
			}
			arg.RoomNumber = RoomNum;
			hThread = CreateThread(NULL, 0, ProcessRoom, &arg, 0, NULL);

			// �غ� �Ϸ� �޽��� ������
			for (int i = 0; i < MAX_CLIENTS; ++i) {
				char buffer[100];
				sprintf(buffer, "Game is ready for Client %d.", ClientNum);
				send(client_sockets[i], buffer, strlen(buffer), 0);
			}

			// Ŭ��1 ��ȣ on
			SetEvent(events[RoomNum++].hClient1Event);

			// ���̻� ���� ���� ����
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

	// ���� ����
	WSACleanup();
	return 0;
}

#pragma once
#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#include <array>

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

#define SERVERPORT 9000
#define MAX_CLIENTS 2
#define MAX_ROOMS 20

using std::array;

struct RoomArg
{
	array<HANDLE, MAX_ROOMS> Client;
	BYTE RoomNumber;
};

struct ClientArg
{
	SOCKET sock;
	BYTE RoomNumber;	
};

class Events
{
public:
	Events()
	{
		// ������ ��� ���� �̺�Ʈ
		hClient1Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hClient2Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hRoomEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	HANDLE hRoomEvent;
	HANDLE hClient1Event;
	HANDLE hClient2Event;
};

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg);
//{
//	LPVOID lpMsgBuf;
//	FormatMessageA(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char *)&lpMsgBuf, 0, NULL);
//	MessageBoxA(NULL, (const char *)lpMsgBuf, msg, MB_ICONERROR);
//	LocalFree(lpMsgBuf);
//	exit(1);
//}

// ���� �Լ� ���� ���
void err_display(const char* msg);
//{
//	LPVOID lpMsgBuf;
//	FormatMessageA(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char *)&lpMsgBuf, 0, NULL);
//	printf("[%s] %s\n", msg, (char *)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}

// ���� �Լ� ���� ���
void err_display(int errcode);
//{
//	LPVOID lpMsgBuf;
//	FormatMessageA(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, errcode,
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char *)&lpMsgBuf, 0, NULL);
//	printf("[����] %s\n", (char *)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}

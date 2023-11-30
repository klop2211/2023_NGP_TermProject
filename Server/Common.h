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
#include <iostream>

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

#include <windef.h>

#define SERVERPORT 9000
#define MAX_CLIENTS 2
#define MAX_ROOMS 20
#define Client1 0
#define Client2 1
#define StateMsgNone 0

#define CLIENTWINWIDTH	1600
#define CLIENTWINHEIGHT	900

using std::array;

// �޼����� ��� ����, �̰ź��� ������ ���� ���� �� �� ����
typedef BYTE StateMsgByte;

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
	Events();
	~Events();

	HANDLE hRoomEvent;
	HANDLE hClient1Event;
	HANDLE hClient2Event;
};

struct FPOINT
{
	FPOINT() {}
	FPOINT(float x, float y) { this->x = x; this->y = y; }

	float x;
	float y;
};

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg);

// ���� �Լ� ���� ���
void err_display(const char* msg);

// ���� �Լ� ���� ���
void err_display(int errcode);

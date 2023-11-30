#pragma once
#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#include <array>
#include <iostream>

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

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

// 메세지의 헤더 역할, 이거보고 다음에 뭐가 올지 알 수 있음
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

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg);

// 소켓 함수 오류 출력
void err_display(const char* msg);

// 소켓 함수 오류 출력
void err_display(int errcode);

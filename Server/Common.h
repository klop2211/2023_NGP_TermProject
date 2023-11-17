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

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

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
		// 쓰레드 제어를 위한 이벤트
		hClient1Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hClient2Event = CreateEvent(NULL, FALSE, FALSE, NULL);
		hRoomEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	HANDLE hRoomEvent;
	HANDLE hClient1Event;
	HANDLE hClient2Event;
};

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// 소켓 함수 오류 출력
void err_display(int errcode);
//{
//	LPVOID lpMsgBuf;
//	FormatMessageA(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, errcode,
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(char *)&lpMsgBuf, 0, NULL);
//	printf("[오류] %s\n", (char *)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}

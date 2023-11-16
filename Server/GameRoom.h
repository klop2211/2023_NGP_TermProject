#pragma once
struct RoomArg
{
	HANDLE Client1;
	HANDLE Client2;
};

DWORD WINAPI ProcessRoom(LPVOID arg);
#pragma once

enum WolfStatus { Wolf_Move, Wolf_Dead, Wolf_Attact, Wolf_Hit, Wolf_Die };
enum BatStatus { Bat_Move, Bat_Dead, Bat_Attact, Bat_Hit, Bat_Die };
enum Status{ Ice_s = 1, Fire_s, NULL_S };
enum PapyrusStatus {UP_Breaking = 0, UP_Move, UP_Pattern,
					P_Move = 0, P_Down, P_Pattern1, P_Pattern2, P_Die};

class _Object {
public:
	POINT size, offset;			//위치, 크기
	CImage* img;				//출력할 이미지
	RECT hitBox;				//히트박스이자 좌표
	int count, wait;			//스프라이트 교체용 count, Draw 횟수를 조정하기 위한 wait

	int hp, maxHp, att, speed;
};

struct _Object_Node {
	_Object* data;
	_Object_Node* next;
};

#include "Bat.h"
#include "Wolf.h"
#include "Bone.h"
#include "Papyrus.h"
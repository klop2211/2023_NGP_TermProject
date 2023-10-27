#pragma once

enum WolfStatus { Wolf_Move, Wolf_Dead, Wolf_Attact, Wolf_Hit, Wolf_Die };
enum BatStatus { Bat_Move, Bat_Dead, Bat_Attact, Bat_Hit, Bat_Die };
enum Status{ Ice_s = 1, Fire_s, NULL_S };
enum PapyrusStatus {UP_Breaking = 0, UP_Move, UP_Pattern,
					P_Move = 0, P_Down, P_Pattern1, P_Pattern2, P_Die};

class _Object {
public:
	POINT size, offset;			//��ġ, ũ��
	CImage* img;				//����� �̹���
	RECT hitBox;				//��Ʈ�ڽ����� ��ǥ
	int count, wait;			//��������Ʈ ��ü�� count, Draw Ƚ���� �����ϱ� ���� wait

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
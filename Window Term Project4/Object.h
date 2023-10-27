#pragma once

enum Direction { Left, Right };
enum ObjectType {
	Drop_Spear = 100, Meteor_Spear, Explosion, Wall, Hurricane, None, Ice, Fire, Knockdown, SowrdLight,
	Rotation_Spear, Airborne_Spear, Red_Spear, Earthquake, Flame_Zone, Drop_Red_Spear, Yellow_Spear, Purple_Spear
};

struct Oder {
	POINT speed = { 0,0 };
	int spawn_object_type = -1;
};

class Object
{
public:
	Object();
	~Object();
	void SetSpeed(const int& x, const int& y);
	void SetImage(const TCHAR[]);
	void SetRect(const int& left, const int& top, const int& right, const int& bottom);
	void SetDelay(const int& num);
	void SetBaseDelay(const int& num);
	void SetOder(const int& index, const POINT& speed, const int& spawn_object_type);
	void SetFrame_Now(const int& num) { frame_now = num; }
	void SetDamage(const int& num) { damage = num; }
	void SetDestruction(const int& num) { destruction = num; }
	void SetNeutralization(const int& num) { neutralization = num; }
	void SetNamed_Damage(const int& num) { named_damage = num; }
	void SetType(const ObjectType& num) { type = num; }
	void SetAttacknums(const int& num) { attack_nums = num; }
	void SetSeedDamage(const int& num) { seed_damage = num; }
	int GetSeedDamage() { return seed_damage; }
	Oder GetOder(const int& index);
	int GetFrame_Max();
	int GetDelay();
	int GetBaseDelay();
	int GetDirection();
	int GetFrame_Now();
	int GetDamage() { return damage; }
	int GetDestruction() { return destruction; }
	int GetNeutralization() { return neutralization; }
	int GetNamed_Damage() { return named_damage; }
	ObjectType GetType() { return type; }
	int GetAttacknums() { return attack_nums; }
	RECT GetRect() { return rect; }
	RECT* GetRect(int numm) { return &rect; }

	POINT GetSpeed() {
		return { speed_x, speed_y };
	}
	bool Check_HItList(_Object* hitpointer);
	void DelayMinus();
	void PlusFrame_Now();
	void Move(const int& bottom);
	void Draw(HDC memdc, const int& num);
	void Draw(HDC memdc);
	void Insert_Hitlist(_Object* hitpointer);
	void Delete_Hitlist();
protected:
	int damage, named_damage, seed_damage, destruction, neutralization, delay, base_delay, frame_max, frame_now, speed_x, speed_y, dir, attack_nums;
	ObjectType type;
	Oder frame_oder[20];
	_Object_Node* hit_list;
	CImage img;
	RECT rect;
};

Object::Object()
{
	damage = destruction = neutralization = speed_y = named_damage = attack_nums = seed_damage = 0;
	type = None;
	rect = { 0,0,0,0 };
	dir = Right;
	img.Load(L"./\\윈플 텀프 이미지\\창술사_move.png");
	speed_x = 5;
	frame_max = img.GetHeight() / 32;
	delay = base_delay = 10;
	frame_now = 0;
	for (int i = 0; i < 20; i++)
		frame_oder[i] = { 0,0,-1 };
	hit_list = new _Object_Node;
	hit_list->next = NULL;
}

Object::~Object()
{
	img.Destroy();
	Delete_Hitlist();
	delete hit_list;
}
int Object::GetDelay() {
	return delay;
}
int Object::GetBaseDelay() {
	return base_delay;
}

int Object::GetFrame_Max() {
	return frame_max;
}
int Object::GetDirection() {
	return dir;
}
int Object::GetFrame_Now() {
	return frame_now;
}

Oder Object::GetOder(const int& index) {
	return frame_oder[index];
}

void Object::SetSpeed(const int& x, const int& y) {
	if (x < 0)
		dir = Left;
	else if (x > 0)
		dir = Right;
	speed_x = x;
	speed_y = y;
}

void Object::SetImage(const TCHAR str[]) {
	img.Destroy();
	img.Load(str);
	frame_max = img.GetHeight() / 32;
	frame_now = 0;
}


void Object::SetRect(const int& left, const int& top, const int& right, const int& bottom) {
	rect = { left, top, right, bottom };
}

void Object::SetDelay(const int& num) {
	delay = num;
}
void Object::SetBaseDelay(const int& num) {
	base_delay = num;
	delay = num;
}
void Object::SetOder(const int& index, const POINT& speed, const int& spawn_object_type) {
	frame_oder[index] = { speed, spawn_object_type };
}


void Object::Move(const int& bottom) {
	int height = rect.bottom - rect.top;
	rect.left += speed_x;
	rect.right += speed_x;
	rect.top -= speed_y;
	rect.bottom -= speed_y;
	if (rect.bottom > bottom) {
		rect.bottom = bottom;
		rect.top = rect.bottom - height;
	}
}

void Object::DelayMinus() {
	delay--;
}
void Object::PlusFrame_Now() {
	frame_now++;
}


void Object::Draw(HDC memdc, const int& num) {
	img.Draw(memdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, img.GetHeight() / frame_max * num, img.GetWidth(), img.GetHeight() / frame_max);
}
void Object::Draw(HDC memdc) {
	img.Draw(memdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, img.GetHeight() / frame_max * frame_now, img.GetWidth(), img.GetHeight() / frame_max);
}

void Object::Insert_Hitlist(_Object* hitpointer) {
	_Object_Node* newNode = new _Object_Node;
	newNode->data = hitpointer;
	newNode->next = hit_list->next;
	hit_list->next = newNode;
}

bool Object::Check_HItList(_Object* hitpointer) {
	for (_Object_Node* p = hit_list; p->next != NULL; p = p->next) {
		if (p->next->data == hitpointer) {
			return true;
		}
	}
	return false;
}

void Object::Delete_Hitlist() {
	_Object_Node* p = hit_list;
	while (p->next != NULL) {
		_Object_Node* target = p->next;
		p->next = p->next->next;
		delete target;
		if (p->next != NULL)
			p = p->next;
	}
}
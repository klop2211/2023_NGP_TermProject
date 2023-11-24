#pragma once

struct FPOINT
{
	float x;
	float y;
};

// ��ũ���� �׷��� ������Ʈ�� ����
class Object
{
public:
	Object() {}
	~Object() {}

	virtual void Update(float elapsed) {};

	//Render
public:
	virtual void Draw(HDC& memdc) {};

	//Gettor, Settor
public:
	virtual CImage GetImg() const = 0;
	RECT GetRect() const { return m_rRect; }

protected:
	// ���� �̹���
	// CImage* m_cImg;

	//�浹 ó�� �簢��
	RECT m_rRect;

	// �ؽ��� ��ġ
	POINT m_pPoint;

	// �ؽ��� ������
	POINT m_pOffset;

	// ������Ʈ ��ġ
	FPOINT m_Location;
};


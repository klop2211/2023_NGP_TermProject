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

	virtual void Update(float elapsed) = 0;

	//Render
public:
	virtual void Draw(HDC& memdc) = 0;
	//Gettor, Settor
public:
	virtual CImage GetImg() const = 0;
	RECT GetRect() const { return m_rRect; }

protected:
	// ���� �̹���
	// CImage* m_cImg;

	//�浹 ó�� �簢��
	RECT m_rRect;

	// �ؽ��� ��ġ ������
	POINT m_pPoint, m_pOffset;
	FPOINT m_Location;
};


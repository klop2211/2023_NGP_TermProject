#pragma once

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
	CImage* GetImg() const { return m_cImg; }
	RECT GetRect() const { return m_rRect; }

protected:
	// ���� �̹���
	CImage* m_cImg;

	//�浹 ó�� �簢��
	RECT m_rRect;

	// ��ġ ũ��
	POINT m_pPoint, m_pOffset;
};


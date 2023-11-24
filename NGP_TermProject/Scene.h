#pragma once
class Scene
{
public:
	Scene();
	~Scene();

	void Update(float elapsed);
	void Draw(HDC& memDc);

private:
	Player* m_pPlayer;
	std::list<Object*> m_lObjectList;

};


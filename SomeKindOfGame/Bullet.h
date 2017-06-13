#pragma once
#include "GameObject.h"
#include <vector>
#include "Wall.h"
#include <cmath>

class Bullet:public GameObject
{
private:
	std::vector<Wall*>* walls;
	int dir;
	bool isDead;
public:
	Bullet(sf::Vector2f &pos, int dir);
	
	void Update();
	void CheckWall();
	void CheckRoomEdge();

	void MakeDead();
	void Move();

	bool CheckDead();
	void SetWalls(std::vector<Wall*>* walls);

	~Bullet();
};


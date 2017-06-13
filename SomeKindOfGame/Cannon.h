#pragma once
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "Bullet.h"

class Cannon:public GameObject
{
private:
	int dir;

	int prevShootTime;
	int shootDelay;
	int shootOffset;
	int frameCounter;

	std::vector<Wall*>* walls;
	std::vector<Bullet*>* bullets;

	sf::Texture* bulletTexture;
public:
	Cannon(sf::Vector2f,int, std::vector<Bullet*>*);
	
	void Shoot();
	void Update();
	void SetDelay(int);
	void SetOffset(int);
	void RefreshOffset();

	void SetWalls(std::vector<Wall*>* walls);
	void SetBulletTexture(sf::Texture* texture);


	std::vector<Bullet*>* GetBullets();

	//~Cannon();
};


#include "Cannon.h"
#include <ctime>


Cannon::Cannon(sf::Vector2f pos, int dir, std::vector<Bullet*>* bullets)
{
	this->pos = pos;
	this->dir = dir;
	this->bullets = bullets;

	frameCounter = 0;
	shootDelay = 1000;
	shootOffset = 0;
	prevShootTime = clock() + shootOffset;

	body.setTexture(texture);
	body.setPosition(this->pos);
	body.setSize(sf::Vector2f(30.f, 30.f));
}

void Cannon::SetDelay(int speed)
{
	shootDelay = speed;
}

void Cannon::SetOffset(int offset)
{
	shootOffset = offset;
	prevShootTime = frameCounter + shootOffset;
}


void Cannon::Shoot()
{
	if (frameCounter - prevShootTime > shootDelay) 
	{
		Bullet* bull = new Bullet(pos + sf::Vector2f(15.f, 15.f), dir);
		bull->SetWalls(walls);
		bull->SetTexture(bulletTexture);
		bullets->push_back(bull);
		prevShootTime = frameCounter;
	}
}

void Cannon::RefreshOffset()
{
	prevShootTime = frameCounter + shootOffset;
}

void Cannon::SetWalls(std::vector<Wall*>* walls)
{
	this->walls = walls;
}



void Cannon::SetBulletTexture(sf::Texture* texture)
{
	this->bulletTexture = texture;
}


void Cannon::Update()
{
	Shoot();
	frameCounter++;
}


/*Cannon::~Cannon()
{
}
*/
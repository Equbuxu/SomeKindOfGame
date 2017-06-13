#include "Bullet.h"



Bullet::Bullet(sf::Vector2f &pos, int dir)
{
	this->pos = pos;
	this->dir = dir;

	isDead = false;

	body.setTexture(texture);
	body.setPosition(this->pos);
	body.setSize(sf::Vector2f(4.f, 4.f));
	body.setOrigin(sf::Vector2f(2.f, 2.f));
}

void Bullet::Update()
{
	if (!isDead)
	{
		CheckWall();
		CheckRoomEdge();
		Move();
	}
}

void Bullet::Move()
{
	switch (dir)
	{
	case 0:
		pos.x += 5;
		break;
	case 1:
		pos.y -= 5;
		break;
	case 2:
		pos.x -= 5;
		break;
	case 3:
		pos.y += 5;
		break;
	}
	body.setPosition(this->pos);
}

bool Bullet::CheckDead()
{
	return isDead;
}

void Bullet::CheckRoomEdge()
{
	if (pos.x < 0 || pos.x>780 || pos.y < 0 || pos.y>600) 
	{
		isDead = true;
	}
}

void Bullet::CheckWall()
{
	if (!isDead) {
		for (int i = 0; i < walls->size(); i++)
		{
			sf::Vector2f wallPos(walls->at(i)->GetPosition());
			if (pos.x > wallPos.x && pos.y >= wallPos.y)
			{
				if (pos.x < wallPos.x + 30.f && pos.y < wallPos.y + 30.f)
				{
					isDead = true;
				}
			}
		}
	}
}

void Bullet::MakeDead()
{
	isDead = true;
}

void Bullet::SetWalls(std::vector<Wall*>* walls)
{
	this->walls = walls;
}

Bullet::~Bullet()
{
}

#include "Wall.h"



Wall::Wall(sf::Vector2f &pos)
{
	this->pos = pos;
	body.setSize(sf::Vector2f(30.f, 30.f));
	//body.setFillColor(sf::Color::White);
	body.setPosition(this->pos);
	body.setTexture(texture);
}

void Wall::SetNeighbour(int pos, bool value)
{
	neightbours[pos] = value;
}

bool Wall::GetNeighbour(int pos)
{
	if (pos < 8 && pos>=0)
	{
		return neightbours[pos];
	}
	else
	{
		return false;
	}
}

Wall::~Wall()
{
}

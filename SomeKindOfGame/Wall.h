#pragma once
#include <SFML\Graphics.hpp>
#include "GameObject.h"

class Wall :public GameObject
{
private:
	bool neightbours[8];
public:
	Wall(sf::Vector2f &pos);
	void SetNeighbour(int pos, bool value);
	bool GetNeighbour(int pos);
	~Wall();
};


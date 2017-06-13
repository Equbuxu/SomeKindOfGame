#pragma once
#include "SFML\Graphics.hpp"
#include "GameObject.h"

class Item : public GameObject
{
private:
	bool isPicked;

public:
	Item(sf::Vector2f &pos);

	void Draw(sf::RenderWindow& window);
	bool TryToPick(sf::Vector2f& plPos);

	//~Item();
};


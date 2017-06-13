#include "Item.h"
#include <cmath>


Item::Item(sf::Vector2f &pos)
{
	isPicked = false;
	body.setSize(sf::Vector2f(30.f,30.f));
	body.setPosition(pos);
	this->pos = pos;
}

void Item::Draw(sf::RenderWindow &window)
{
	if (!isPicked) {
		GameObject::Draw(window);
	}
}

bool Item::TryToPick(sf::Vector2f& plPos)
{
	if (!isPicked)
	{
		if (std::pow(pos.x+15.f - plPos.x, 2) + std::pow(pos.y+15.f - plPos.y, 2) < 400.f)
		{
			isPicked = true;
			return true;
		}
	}
	return false;
}

/*Item::~Item()
{
}
*/
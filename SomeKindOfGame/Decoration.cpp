#include "Decoration.h"



void Decoration::SetTexture(sf::Texture* texture)
{
	body.setSize(sf::Vector2f(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y)));
	GameObject::SetTexture(texture);
}

void Decoration::SetLightLevel(int level)
{
	this->lightLevel = level;
}

void Decoration::SetLayer(int layer)
{
	this->layer = layer;
}

void Decoration::Draw(sf::RenderWindow& window)
{
	if (layer == 0)
	{
		window.draw(body);
	}
}

void Decoration::DrawAbove(sf::RenderWindow& window)
{
	if (layer == 1)
	{
		window.draw(body);
	}
}

int Decoration::GetLightLevel()
{
	return lightLevel;
}

sf::Vector2f Decoration::GetSize()
{
	return (sf::Vector2f(static_cast<float>(texture->getSize().x), static_cast<float>(texture->getSize().y)));
}

Decoration::~Decoration()
{
}

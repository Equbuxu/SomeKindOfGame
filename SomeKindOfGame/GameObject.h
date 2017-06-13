#pragma once
#include "SFML\Graphics.hpp"

class GameObject
{
protected:
	sf::RectangleShape body;
	sf::Vector2f pos;
	sf::Texture* texture;

public:
	GameObject(sf::Vector2f &pos);
	GameObject();

	void Draw(sf::RenderWindow& window);
	void SetTexture(sf::Texture* texture);
	void SetPosition(sf::Vector2f pos);

	sf::Vector2f GetPosition();

	

	//~GameObject();
};


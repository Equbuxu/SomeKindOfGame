#pragma once
#include "GameObject.h"

class Decoration : public GameObject
{
private:
	int lightLevel, layer;
public:
	Decoration(sf::Vector2f &pos) :GameObject::GameObject(pos) {};
	void SetTexture(sf::Texture* texture);
	void SetLightLevel(int);
	void Decoration::SetLayer(int layer);
	int GetLightLevel();
	void Draw(sf::RenderWindow& window);
	void DrawAbove(sf::RenderWindow& window);
	sf::Vector2f GetSize();
	~Decoration();
};


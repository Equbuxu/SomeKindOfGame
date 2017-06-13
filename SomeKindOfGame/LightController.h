#pragma once
#include "Wall.h"
#include "Decoration.h"
#include <vector>
#include <SFML\Graphics.hpp>

class LightController
{
private:
	std::vector<Wall*>* walls;
	std::vector<Decoration*>* decorations;
	std::vector<sf::Sprite*> lightSprites;
	std::vector<sf::Texture*>* lightTextures;

	sf::Sprite shadows;

	int lightMode;
	//0 - полная тьма
	//1 - сумерки
	//2 - светло
	
	sf::RenderTexture layer;
public:
	LightController();
	void Draw(sf::RenderWindow& window);
	void SetTextures(std::vector<sf::Texture*>*);
	void SetLightMode(int);
	void SetWalls(std::vector<Wall*>* walls);
	void SetDecorations(std::vector<Decoration*>* decorations);
	~LightController();
};


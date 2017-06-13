#pragma once
#include <vector>
#include "Location.h"
#include "SFML\Graphics.hpp"
#include "Player.h"

class LocManager
{
private:
	std::vector<Location*> locations;
	std::vector<sf::Texture*> wallTextures;
	std::vector<sf::Texture*> itemTextures;
	std::vector<sf::Texture*> cannonTextures;
	std::vector<sf::Texture*> spikeTextures;
	std::vector<sf::Texture*> grChangerTextures;
	std::vector<sf::Texture*> backgroundTextures;
	std::vector<sf::Texture*> decorationTextures;
	std::vector<sf::Texture*> lightTextures;

	std::vector<sf::Texture*> playerTextures;

	std::vector<sf::Sprite*> backgroundSprites;

	sf::Texture bulletTexture;
	sf::Sprite backgroundSprite;

	

	int curLocation;
public:
	LocManager();
	void Update();
	void LoadTextures();
	void LoadPlayerTextures(int);
	void Draw(sf::RenderWindow& window, sf::View& view);
	void LoadWorld();
	void ChangeLocation(int);

	//~LocManager();
};


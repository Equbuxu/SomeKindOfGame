#pragma once
#include <SFML\Graphics.hpp>

class GameOfLife
{
private:
	bool newGrid[26][20];
	bool grid[26][20];

	sf::RectangleShape body;
public:
	GameOfLife();
	
	void Update();
	void Draw(sf::RenderWindow& window);
	
	~GameOfLife();
};


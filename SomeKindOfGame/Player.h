#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Wall.h"
#include "Item.h"
#include "Bullet.h"
#include <cmath>
#include "GameObject.h"
#include "gravityChanger.h"

class Player
{
private:
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acs;
	sf::Vector2f roomSize;

	sf::Font font;
	sf::Text deathsText;
	sf::Text itemsText;

	sf::RectangleShape body;
	std::vector<Wall*>* walls;
	std::vector<Item*>* items;
	std::vector<Bullet*>* bullets;
	std::vector<GameObject*>* spikes;
	std::vector<gravityChanger*>* grChangers;

	std::vector<sf::Texture*>* textures;

	const float walkSpeedLimit = 7;
	const float fallSpeedLimit = 14;

	bool isDead;
	bool wasSticked;
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;

	int curTexture;
	int curFrame;
	int deathsNum;
	int score;
	int gravityDir;


	const sf::Vector2f size = sf::Vector2f(20.f, 20.f);
public:
	Player();

	void Update();
	void Draw(sf::RenderWindow &window);
	void Move();
	void SetPosition(sf::Vector2f pos);
	void SetVel(sf::Vector2f vel);
	void SetRoomSize(sf::Vector2f size);
	
	void DrawTextures(sf::RenderWindow &window);
	void SetTextures(std::vector<sf::Texture*>* textures);
	void DetermineTexture();

	void SetTexture(int);
	void SetWalls(std::vector<Wall*>* walls);
	void SetItems(std::vector<Item*>* items);
	void SetSpikes(std::vector<GameObject*>* spikes);
	void SetGrChangers(std::vector<gravityChanger*>* changers);
	void SetBullets(std::vector<Bullet*>* bullets);

	void CheckSpikes();
	void CheckItems();
	void CheckBullets();
	void CheckGrChangers();
	void SetDead(bool);
	void CheckCollision();
	void SetGravityDir(int);
	void UpdateGuiInfo();

	int GetScore();

	sf::Vector2f GetRelativeSpeed();

	bool CheckDead();
	bool CheckWall(int);

	bool acsTo(int dir, float acs);
	bool addAcsTo(int dir, float acs);

	sf::Vector2f GetSize();
	sf::Vector2f GetPosition();
	
	
	
	//~Player();
};


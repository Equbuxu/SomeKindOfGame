#pragma once
#include <vector>
#include "Wall.h"
#include "Player.h"
#include "Item.h"
#include <string>
#include "Cannon.h"
#include "Bullet.h"
#include "GameObject.h"
#include "gravityChanger.h"
#include "Decoration.h"
#include "LightController.h"
#include "GameOfLife.h"

class Room
{
private:
	std::vector<Wall*> walls;
	std::vector<Item*> items;
	std::vector<Cannon*> cannons;
	std::vector<Bullet*> bullets;
	std::vector<GameObject*> spikes;
	std::vector<gravityChanger*> grChangers;
	std::vector<Decoration*> decorations;

	sf::Sprite* background;

	sf::Vector2f roomSize;

	LightController lControl;

	//GameOfLife life;

	std::string leftRoom = "NoRoom";
	std::string rightRoom = "NoRoom";
	std::string topRoom = "NoRoom";
	std::string bottomRoom = "NoRoom";

public:
	std::string id;

	Room(sf::Vector2f, std::string id);
	
	void SetBackground(sf::Sprite* background);
	void SetId(std::string& id);
	void SetRoom(int dir, std::string name);
	void Room::SetLightLevel(int level);
	void Update();
	void CheckDeadBullets();
	void Draw(sf::RenderWindow &window);
	void DrawLate(sf::RenderWindow &window);
	void DrawShadows(sf::RenderWindow &window);

	void AddWall(sf::Vector2f &pos, sf::Texture* texture, bool[8]);
	void AddItem(sf::Vector2f &pos, sf::Texture* texture);
	void AddSpike(sf::Vector2f &pos, sf::Texture* texture);
	void AddGrChanger(sf::Vector2f &pos,int dir, sf::Texture* texture);
	void AddCannon(sf::Vector2f &pos, int dir, sf::Texture* texture, sf::Texture* bulTexture,int,int);
	void AddDecoration(sf::Vector2f &pos, sf::Texture* texture,int lightLevel,int layer);
	void SetLightTextures(std::vector<sf::Texture*>* lightTextures);
	void RefreshCannonOffsets();
	

	sf::Vector2f GetSize();
	std::vector<Wall*>* GetWalls();
	std::vector<Item*>* GetItems();
	std::vector<GameObject*>* GetSpikes();
	std::vector<Cannon*>* GetCannons();
	std::vector<gravityChanger*>* GetGrChangers();
	std::vector<Bullet*>* GetBullets();

	std::string getRoom(int dir);

	~Room();
};


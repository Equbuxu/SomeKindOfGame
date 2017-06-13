#pragma once
#include <vector>
#include "Room.h"
#include <SFML\Graphics.hpp>
#include <string>

class Location
{
private:
	std::vector<Room*> rooms;
	Player player;

	int curRoom;
	int winScore;
public:
	Location();
	void Update();
	void Draw(sf::RenderWindow &window);
	void AddRoom(Room* room);
	void Location::SetPlayerPosition(sf::Vector2f pos);
	void Location::AttachPlayer();
	void SetWinScore(int);
	void setDefaultGravity(int);
	void SetPlayerTextures(std::vector<sf::Texture*>* textures);

	int GetPlayerScore();
	int GetWinScore();
	int defaultGravity;

	sf::Vector2f Location::GetPlayerSize();
	sf::Vector2f Location::GetPlayerPosition();
	sf::Vector2f GetCurRoomSize();

	std::string GetRoom(int dir);

	bool Location::ChangeRoom(std::string room);
	bool Location::ChangeRoom(int num);

	//~Location();
};


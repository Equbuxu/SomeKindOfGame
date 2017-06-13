#include "Location.h"
#include <iostream>


Location::Location()
{
	curRoom = 0;

	
}


sf::Vector2f Location::GetCurRoomSize()
{
	return rooms[curRoom]->GetSize();
}

void Location::SetPlayerTextures(std::vector<sf::Texture*>* textures)
{
	player.SetTextures(textures);
}

void Location::AttachPlayer()
{
	player.SetPosition(sf::Vector2f(400.f, 300.f));
	player.SetWalls(rooms[curRoom]->GetWalls());
	player.SetItems(rooms[curRoom]->GetItems());
	player.SetRoomSize(rooms[curRoom]->GetSize());
	player.SetBullets(rooms[curRoom]->GetBullets());
	player.SetSpikes(rooms[curRoom]->GetSpikes());;
	player.SetGrChangers(rooms[curRoom]->GetGrChangers());
	player.SetGravityDir(defaultGravity);
}

int Location::GetPlayerScore()
{
	return player.GetScore();
}

int Location::GetWinScore()
{
	return winScore;
}

void Location::SetWinScore(int score)
{
	winScore = score;
}

void Location::Update()
{
	rooms[curRoom]->Update();
	player.Update();

	if (player.CheckDead())
	{
		ChangeRoom(0);
		player.SetPosition(sf::Vector2f(400.f, 300.f));
		player.SetDead(false);
		player.SetGravityDir(defaultGravity);
		player.SetVel(sf::Vector2f(0.f,0.f));
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
	{
		player.SetGravityDir(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
	{
		player.SetGravityDir(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
	{
		player.SetGravityDir(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
	{
		player.SetGravityDir(3);
	}*/

	if (player.GetPosition().y < 0 + player.GetSize().y / 2)
	{
		if (ChangeRoom(rooms[curRoom]->getRoom(1)))
		{
			SetPlayerPosition(sf::Vector2f(player.GetPosition().x, rooms[curRoom]->GetSize().y - GetPlayerSize().y / 2));
		}
	}
	else if (player.GetPosition().y > rooms[curRoom]->GetSize().y - player.GetSize().y / 2)
	{
		if (ChangeRoom(rooms[curRoom]->getRoom(3)))
		{
			SetPlayerPosition(sf::Vector2f(player.GetPosition().x, 0.f + player.GetSize().y / 2));
		}
	}

	if (player.GetPosition().x < 0 + GetPlayerSize().x / 2)
	{
		if (ChangeRoom(rooms[curRoom]->getRoom(2)))
		{
			SetPlayerPosition(sf::Vector2f(rooms[curRoom]->GetSize().x - player.GetSize().x / 2, player.GetPosition().y));
		}
	}
	else if (player.GetPosition().x > rooms[curRoom]->GetSize().x - player.GetSize().x / 2)
	{
		if (ChangeRoom(rooms[curRoom]->getRoom(0)))
		{
			SetPlayerPosition(sf::Vector2f(0.f + player.GetSize().x / 2, player.GetPosition().y));
		}
	}

	
}

void Location::setDefaultGravity(int dir)
{
	defaultGravity = dir;
}

sf::Vector2f Location::GetPlayerSize()
{
	return player.GetSize();
}

void Location::SetPlayerPosition(sf::Vector2f pos)
{
	player.SetPosition(pos);
}

sf::Vector2f Location::GetPlayerPosition()
{
	return player.GetPosition();
}

std::string Location::GetRoom(int dir)
{
	return rooms[curRoom]->getRoom(dir);
}

void Location::Draw(sf::RenderWindow &window)
{
	rooms[curRoom]->Draw(window); 
	player.Draw(window);
	rooms[curRoom]->DrawLate(window);
	rooms[curRoom]->DrawShadows(window);
}

bool Location::ChangeRoom(std::string room)
{
	if (room == "NoRoom")
	{
		return false;
	}
	for (int i = 0; i < rooms.size(); i++)
	{
		if (rooms[i]->id == room)
		{
			curRoom = i;
			player.SetWalls(rooms[curRoom]->GetWalls());
			player.SetItems(rooms[curRoom]->GetItems());
			player.SetRoomSize(rooms[curRoom]->GetSize());
			player.SetBullets(rooms[curRoom]->GetBullets());
			player.SetSpikes(rooms[curRoom]->GetSpikes());
			player.SetGrChangers(rooms[curRoom]->GetGrChangers());
			rooms[i]->RefreshCannonOffsets();
			return true;
		}
	}
	return false;
}

bool Location::ChangeRoom(int num)
{
	if (num < rooms.size()) {
		curRoom = num;
		player.SetWalls(rooms[curRoom]->GetWalls());
		player.SetItems(rooms[curRoom]->GetItems());
		player.SetRoomSize(rooms[curRoom]->GetSize());
		player.SetBullets(rooms[curRoom]->GetBullets());
		player.SetSpikes(rooms[curRoom]->GetSpikes());
		player.SetGrChangers(rooms[curRoom]->GetGrChangers());
		rooms[num]->RefreshCannonOffsets();
		return true;
	}
	return false;
}

void Location::AddRoom(Room* room)
{
	rooms.push_back(room);
}

/*Location::~Location()
{
}*/

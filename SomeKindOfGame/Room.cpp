#include "Room.h"

Room::Room(sf::Vector2f roomSize, std::string id)
{
	this->roomSize = roomSize;
	this->id = id;
}

void Room::SetBackground(sf::Sprite* background)
{
	this->background = background;
}

std::vector<Wall*>* Room::GetWalls()
{
	return &walls;
}

std::vector<Item*>* Room::GetItems()
{
	return &items;
}

std::vector<GameObject*>* Room::GetSpikes()
{
	return &spikes;
}

std::vector<Cannon*>* Room::GetCannons()
{
	return &cannons;
}

std::vector<Bullet*>* Room::GetBullets()
{
	return &bullets;
}

std::vector<gravityChanger*>* Room::GetGrChangers()
{
	return &grChangers;
}

void Room::RefreshCannonOffsets()
{
	for (std::vector<Cannon*>::iterator iter = cannons.begin(); iter != cannons.end(); iter++) {
		(*iter)->RefreshOffset();
	}
}

void Room::Draw(sf::RenderWindow &window) {
	window.draw(*background);
	for (int i = 0; i < decorations.size(); i++)
	{
		decorations[i]->Draw(window);
	}
	for (std::vector<Wall*>::iterator iter = walls.begin(); iter != walls.end(); iter++) {
		(*iter)->Draw(window);
	}
	for (std::vector<Item*>::iterator iter = items.begin(); iter != items.end(); iter++) {
		(*iter)->Draw(window);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Draw(window);
	}
	for (int i = 0; i < spikes.size(); i++)
	{
		spikes[i]->Draw(window);
	}
	for (int i = 0; i < grChangers.size(); i++)
	{
		grChangers[i]->Draw(window);
	}
	for (std::vector<Cannon*>::iterator iter = cannons.begin(); iter != cannons.end(); iter++) {
		(*iter)->Draw(window);
	}
	for (int i = 0; i < decorations.size(); i++)
	{
		decorations[i]->DrawAbove(window);
	}
	//life.Draw(window);
}

void Room::DrawLate(sf::RenderWindow &window) {
	for (int i = 0; i < decorations.size(); i++)
	{
		decorations[i]->DrawAbove(window);
	}
}

void Room::DrawShadows(sf::RenderWindow &window)
{
	lControl.Draw(window);
}

sf::Vector2f Room::GetSize()
{
	return roomSize;
}

void Room::AddWall(sf::Vector2f &pos, sf::Texture* texture, bool neighbours[8]) {
	Wall* wall = new Wall(pos);
	wall->SetTexture(texture);
	for (int i = 0; i < 8; i++)
	{
		wall->SetNeighbour(i, neighbours[i]);
	}	
	walls.push_back(wall);
}

void Room::AddItem(sf::Vector2f &pos, sf::Texture* texture)
{
	Item* item = new Item(pos);
	item->SetTexture(texture);
	items.push_back(item);
}

void Room::AddSpike(sf::Vector2f &pos, sf::Texture* texture)
{
	GameObject* spike = new GameObject(pos);
	spike->SetTexture(texture);
	spikes.push_back(spike);
}

void Room::AddGrChanger(sf::Vector2f &pos,int dir, sf::Texture* texture)
{
	gravityChanger* changer = new gravityChanger(pos);
	changer->setDir(dir);
	changer->SetTexture(texture);
	grChangers.push_back(changer);
}

void Room::AddCannon(sf::Vector2f &pos,int dir, sf::Texture* texture, sf::Texture* bulTexture, int delay, int offset)
{
	Cannon* cannon = new Cannon(pos, dir, &bullets);
	cannon->SetTexture(texture);
	cannon->SetWalls(&walls);
	cannon->SetBulletTexture(bulTexture);
	cannon->SetDelay(delay);
	cannon->SetOffset(offset);

	cannons.push_back(cannon);
}

void Room::AddDecoration(sf::Vector2f &pos, sf::Texture* texture, int lightLevel, int layer)
{
	Decoration* dec = new Decoration(pos);
	dec->SetTexture(texture);
	dec->SetLightLevel(lightLevel);
	dec->SetLayer(layer);
	decorations.push_back(dec);
}

void Room::CheckDeadBullets()
{
	for (int i = static_cast<int>(bullets.size()) - 1; i >= 0; i--)
	{
		if (bullets[i]->CheckDead())
		{
			delete bullets[i];

			bullets.erase(bullets.begin() + i);
		}
	}
}

void Room::Update() {
	for (int i = 0; i<cannons.size(); i++) {
		cannons[i]->Update();
	}
	CheckDeadBullets();
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update();
	}

	//life.Update();
}

void Room::SetId(std::string& id)
{
	this->id = id;
}

void Room::SetLightTextures(std::vector<sf::Texture*>* lightTextures)
{
	lControl.SetTextures(lightTextures);
	lControl.SetDecorations(&decorations);
	lControl.SetWalls(&walls);
}

void Room::SetLightLevel(int level)
{
	lControl.SetLightMode(level);
}

std::string Room::getRoom(int dir)
{
	switch (dir)
	{
	case 0:
		return rightRoom;
		break;
	case 1:
		return topRoom;
		break;
	case 2:
		return leftRoom;
		break;
	case 3:
		return bottomRoom;
		break;
	}
	return "NoRoom";
}

void Room::SetRoom(int dir, std::string name) // 0 = right, 1 = up, 2 = left,3 = down
{
	switch (dir)
	{
	case 0:
		rightRoom = name;
		break;
	case 1:
		topRoom = name;
		break;
	case 2:
		leftRoom = name;
		break;
	case 3:
		bottomRoom = name;
		break;
	}
}


Room::~Room()
{
}

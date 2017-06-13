#include "LightController.h"



LightController::LightController()
{
	layer.create(780, 600);
	shadows.setTexture(layer.getTexture());
	shadows.setScale(1.f, -1.f);
	shadows.setPosition(0.f, 600.f);
}

void LightController::SetWalls(std::vector<Wall*>* walls)
{
	this->walls = walls;
}

void LightController::SetDecorations(std::vector<Decoration*>* decorations)
{
	this->decorations = decorations;
}

void LightController::Draw(sf::RenderWindow& window)
{
	switch (lightMode)
	{
	case 0:
		layer.clear();
		break;
	case 1:
		layer.clear(sf::Color(0, 0, 0, 128));
		break;
	case 2:
		layer.clear(sf::Color(0, 0, 0, 0));
		break;
	}

	for (int i = 0; i < decorations->size(); i++)
	{
		if (decorations->at(i)->GetLightLevel() > 0)
		{
			lightSprites.at(4)->setPosition(decorations->at(i)->GetPosition() + sf::Vector2f(decorations->at(i)->GetSize().x / 2, decorations->at(i)->GetSize().y / 2));
			layer.draw(*lightSprites[4], sf::BlendNone);
		}
	}

	for (int i = 0; i < walls->size(); i++)
	{
		if (walls->at(i)->GetNeighbour(0) && walls->at(i)->GetNeighbour(2) && walls->at(i)->GetNeighbour(4) && walls->at(i)->GetNeighbour(6))
		{ //если соседи со всех четырех сторон
			int freeCornersNum = 0; //колво свободных углов = 0
			int freeCorner = -1; //номер свободного угла
			for (int j = 1; j < 8; j+=2)
			{
				if (!walls->at(i)->GetNeighbour(j))
				{
					freeCorner = j;
					freeCornersNum++;
				}
			}
			if (freeCornersNum == 0)
			{
				lightSprites.at(5)->setPosition(walls->at(i)->GetPosition());
				layer.draw(*lightSprites[5], sf::BlendAlpha);
			}
			else if (freeCornersNum == 1)
			{
				int spriteNum;
				switch (freeCorner)
				{
				case 1:
					spriteNum = 13;
					break;
				case 3:
					spriteNum = 12;
					break;
				case 5:
					spriteNum = 11;
					break;
				case 7:
					spriteNum = 10;
					break;
				} //выбор нужного спрайта в зависимости от пустого угла
				lightSprites.at(spriteNum)->setPosition(walls->at(i)->GetPosition());
				layer.draw(*lightSprites[spriteNum], sf::BlendAlpha);
			}
			else if (freeCornersNum = 2)
			{
				int spriteNum;
				if (!walls->at(i)->GetNeighbour(1))
				{
					if (!walls->at(i)->GetNeighbour(7))
					{
						spriteNum = 0;
					}
					if (!walls->at(i)->GetNeighbour(3))
					{
						spriteNum = 1;
					}
				}
				if (!walls->at(i)->GetNeighbour(5))
				{
					if (!walls->at(i)->GetNeighbour(7))
					{
						spriteNum = 2;
					}
					if (!walls->at(i)->GetNeighbour(3))
					{
						spriteNum = 2;
					}
				}
				lightSprites.at(spriteNum)->setPosition(walls->at(i)->GetPosition());
				layer.draw(*lightSprites[spriteNum], sf::BlendAlpha);
			}
		}
		else //очень запутанная и кривая система выбора нужного спрайта
		{
			int neighsNum = 0;

			for (int j = 0; j < 8; j += 2)
			{
				if (walls->at(i)->GetNeighbour(j))
				{
					neighsNum++;
				}
			}

			int spriteNum = -1;

			if (neighsNum == 3)
			{
				if (!walls->at(i)->GetNeighbour(0))
				{
					if (walls->at(i)->GetNeighbour(5))
					{
						if (walls->at(i)->GetNeighbour(3))
						{
							spriteNum = 0;
						}
						else
						{
							spriteNum = 7;
						}
						
					}
					else if (walls->at(i)->GetNeighbour(3)){
						spriteNum = 8;
					}
				}
				else if (!walls->at(i)->GetNeighbour(2))
				{
					if (walls->at(i)->GetNeighbour(5))
					{
						if (walls->at(i)->GetNeighbour(7))
						{
							spriteNum = 1;
						}
						else
						{
							spriteNum = 7;
						}
					}
					else if (walls->at(i)->GetNeighbour(7)) {
						spriteNum = 6;
					}
				}
				else if (!walls->at(i)->GetNeighbour(4))
				{
					if (walls->at(i)->GetNeighbour(1))
					{
						if (walls->at(i)->GetNeighbour(7))
						{
							spriteNum = 2;
						}
						else
						{
							spriteNum = 9;
						}

					}
					else if (walls->at(i)->GetNeighbour(7)) {
						spriteNum = 6;
					}
				}
				else
				{
					if (walls->at(i)->GetNeighbour(1))
					{
						if (walls->at(i)->GetNeighbour(3))
						{
							spriteNum = 3;
						}
						else
						{
							spriteNum = 9;
						}

					}
					else if (walls->at(i)->GetNeighbour(3)) {
						spriteNum = 8;
					}
				}
				if (spriteNum != -1)
				{
					lightSprites.at(spriteNum)->setPosition(walls->at(i)->GetPosition());
					layer.draw(*lightSprites[spriteNum], sf::BlendAlpha);
				}
			}
			else if (neighsNum == 2)
			{
				if (walls->at(i)->GetNeighbour(2))
				{
					if (walls->at(i)->GetNeighbour(4) && walls->at(i)->GetNeighbour(3))
					{
						spriteNum = 8;
					}
					else if (walls->at(i)->GetNeighbour(0) && walls->at(i)->GetNeighbour(1))
					{
						spriteNum = 9;
					}
					
				}
				else if (walls->at(i)->GetNeighbour(6))
				{
					if (walls->at(i)->GetNeighbour(4) && walls->at(i)->GetNeighbour(5))
					{
						spriteNum = 7;
					}
					else if (walls->at(i)->GetNeighbour(0) && walls->at(i)->GetNeighbour(7))
					{
						spriteNum = 6;
					}
				}
				if (spriteNum != -1)
				{
					lightSprites.at(spriteNum)->setPosition(walls->at(i)->GetPosition());
					layer.draw(*lightSprites[spriteNum], sf::BlendAlpha);
				}
			}
		}
	}

	window.draw(shadows);
}

void LightController::SetLightMode(int mode)
{
	lightMode = mode;
	switch (lightMode)
	{
	case 0:
		for (int i = 0; i < lightSprites.size(); i++)
		{
			lightSprites.at(i)->setColor(sf::Color(255, 255, 255, 255));
		}
		break;
	case 1:
		for (int i = 0; i < lightSprites.size(); i++)
		{
			lightSprites.at(i)->setColor(sf::Color(255,255,255,200));
		}
		lightSprites.at(4)->setColor(sf::Color(255, 255, 255, 128));
		break;
	case 2:
		for (int i = 0; i < lightSprites.size(); i++)
		{
			lightSprites.at(i)->setColor(sf::Color(255, 255, 255, 128));
		}
		lightSprites.at(4)->setColor(sf::Color(255, 255, 255, 0));
		break;
	}
}

void LightController::SetTextures(std::vector<sf::Texture*>* textures)
{
	this->lightTextures = textures;
	for (int i = 0; i < lightTextures->size();i++)
	{
		sf::Sprite* sprite = new sf::Sprite();
		sprite->setTexture(*lightTextures->at(i));
		lightSprites.push_back(sprite);
	}
	lightSprites[4]->setOrigin(lightSprites[4]->getTextureRect().width/2, lightSprites[4]->getTextureRect().height / 2);
}

LightController::~LightController()
{
}

#include "LocManager.h"
#include <fstream>
#include <string>
#include <iostream>

LocManager::LocManager()
{
	curLocation = 0;
	LoadTextures();
	LoadWorld();
}

void LocManager::ChangeLocation(int loc)
{
	if (loc < locations.size() && loc >=0)
	{
		curLocation = loc;
		locations[curLocation]->AttachPlayer();
		locations[curLocation]->ChangeRoom(0);
	}
}

void LocManager::LoadWorld()
{
	std::ifstream lin("World/location-data.ldf");

	if (!lin.is_open())
	{
		std::cout << "Could not open location data file" << std::endl;
	}

	int locNumber;
	lin >> locNumber;

	for (int j = 0;j<locNumber;j++) 
	{
		int input, grav, winSc;
		lin >> input;
		Location* loc = new Location;
		lin >> winSc;
		loc->SetWinScore(winSc);
		lin >> grav;
		loc->setDefaultGravity(grav);

		loc->SetPlayerTextures(&playerTextures);

		for (int i = 0; i < input; i++) 
		{
			std::ifstream rin("World/" + std::to_string(j) +"/" + std::to_string(i)+ ".rdf");
			
			if (!rin.is_open())
			{
				std::cout << "Could not open room data file. " << "(room:" << std::to_string(i) << ",loc:" << std::to_string(j) << ")" << std::endl;
			}

			std::string str, name;
			std::string rooms[4];


			float sizex, sizey;

			int bgNum, lightLevel;

			rin >> sizex;
			rin >> sizey;
			rin >> name;
			rin >> bgNum;
			rin >> lightLevel;

			if (sizex <= 0 || sizey <= 0)
			{
				std::cout << "Incorrect room size. " << "(room:" << std::to_string(i) << ",loc:" << std::to_string(j) << ")" << std::endl;
			}

			Room* room = new Room(sf::Vector2f(sizex, sizey), name);

			room->SetBackground(backgroundSprites[bgNum]);
			

			for (int k = 0; k < 4; k++) 
			{
				rin >> rooms[k];
				if (rooms[k] != "NoRoom")
				{
					room->SetRoom(k, rooms[k]);
				}
			}

			
			rin >> str;
			while (rin) {
				
				if (str == "Wall")
				{
					float posx, posy;
					int textId;

					rin >> posx;
					rin >> posy;
					rin >> textId;

					bool neightbours[8];

					for (int i = 0; i < 8; i++)
					{
						rin >> neightbours[i];
					}

					room->AddWall(sf::Vector2f(posx, posy), wallTextures[textId], neightbours);
				}
				else if (str == "Item")
				{
					float posx, posy;
					int textId;

					rin >> posx;
					rin >> posy;
					rin >> textId;

					room->AddItem(sf::Vector2f(posx, posy), itemTextures[textId]);
				}
				else if (str == "Spike")
				{
					float posx, posy;
					int textId;

					rin >> posx;
					rin >> posy;
					rin >> textId;

					room->AddSpike(sf::Vector2f(posx, posy), spikeTextures[textId]);
				}
				else if (str == "Decoration")
				{
					float posx, posy;
					int textId, lightLevel, layer;

					rin >> posx;
					rin >> posy;
					rin >> textId;
					rin >> lightLevel;
					rin >> layer;

					room->AddDecoration(sf::Vector2f(posx, posy), decorationTextures[textId], lightLevel, layer);
				}
				else if (str == "gravityChanger")
				{
					float posx, posy;
					int textId,dir;

					rin >> posx;
					rin >> posy;
					rin >> dir;
					rin >> textId;

					room->AddGrChanger(sf::Vector2f(posx, posy),dir, grChangerTextures[textId]);
				}
				else if (str == "Cannon")
				{
					float posx, posy;
					int textId,dir,delay,offset;

					rin >> posx;
					rin >> posy;
					rin >> dir;
					rin >> textId;
					rin >> delay;
					rin >> offset;

					room->AddCannon(sf::Vector2f(posx, posy), dir, cannonTextures[textId], &bulletTexture, delay, offset);
				}
				else
				{
					std::cout << "Incorrect object name. " << "(room:" << std::to_string(i) << ",loc:" << std::to_string(j) << ")" << std::endl;
				}
				rin >> str;
			} 

			rin.close();
			room->SetLightTextures(&lightTextures);
			room->SetLightLevel(lightLevel);
			loc->AddRoom(room);
		}
		locations.push_back(loc);
	}

	lin.close();
	locations[curLocation]->AttachPlayer();
}

void LocManager::LoadTextures() 
{
	

	int backgroundNum;
	int cannonNum;
	int grChangerNum;
	int itemNum;
	int spikeNum;
	int wallNum;
	int decorationNum;
	int lightNum;
	int playerNum;

	std::ifstream ist("Resources/rdata.rdf");

	if (!ist.is_open())
	{
		std::cout << "Could not open texture data file" << std::endl;
	}

	ist >> backgroundNum;
	ist >> cannonNum;
	ist >> grChangerNum;
	ist >> itemNum;
	ist >> spikeNum;
	ist >> wallNum;
	ist >> decorationNum;
	ist >> lightNum;
	ist >> playerNum;

	ist.close();

	LoadPlayerTextures(playerNum);

	for (int i = 0; i < wallNum; i++) // загрузка текстур стен
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/Walls/Wall" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(false);
		wallTextures.push_back(curTexture);
	}

	for (int i = 0; i < itemNum; i++) // загрузка текстур предметов
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/Items/Item" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(false);
		itemTextures.push_back(curTexture);
	}

	for (int i = 0; i < spikeNum; i++) // загрузка текстур шипов
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/Spikes/Spike" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(false);
		spikeTextures.push_back(curTexture);
	}

	for (int i = 0; i < cannonNum; i++) // загрузка текстур пушек
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/Cannons/Cannon" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(false);
		cannonTextures.push_back(curTexture);
	}

	for (int i = 0; i < grChangerNum; i++) // загрузка текстур изменятелей гравитации
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/gravityChangers/gravityChanger" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(false);
		grChangerTextures.push_back(curTexture);
	}

	for (int i = 0; i < backgroundNum; i++) // загрузка фонов
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/Backgrounds/Background" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(true);
		backgroundTextures.push_back(curTexture);
		sf::Sprite* curSprite = new sf::Sprite(*curTexture);
		curSprite->setTextureRect({ 0,0,800, 600 });
		backgroundSprites.push_back(curSprite);
	}

	for (int i = 0; i < decorationNum; i++) // загрузка текстур декораций
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/Decorations/Decoration" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(false);
		decorationTextures.push_back(curTexture);
	}

	for (int i = 0; i < lightNum; i++) // загрузка текстур теней
	{
		sf::Texture* curTexture = new sf::Texture();
		curTexture->loadFromFile("Resources/LightGradients/LightGradient" + std::to_string(i) + ".png");
		curTexture->setSmooth(false);
		curTexture->setRepeated(false);
		lightTextures.push_back(curTexture);
	}
	

	bulletTexture.loadFromFile("Resources/Bullet.png"); //загрузка текстуры пули
	bulletTexture.setSmooth(false);
	bulletTexture.setRepeated(true);

}

void LocManager::LoadPlayerTextures(int Number)
{
	sf::Texture* JumpLeftTexture = new sf::Texture();
	JumpLeftTexture->loadFromFile("Resources/Player/JumpLeft.png");
	playerTextures.push_back(JumpLeftTexture);

	sf::Texture* JumpRightTexture = new sf::Texture();
	JumpRightTexture->loadFromFile("Resources/Player/JumpRight.png");
	playerTextures.push_back(JumpRightTexture);

	sf::Texture* StandTexture = new sf::Texture();
	StandTexture->loadFromFile("Resources/Player/Stand.png");
	playerTextures.push_back(StandTexture);

	sf::Texture* StickLeftTexture = new sf::Texture();
	StickLeftTexture->loadFromFile("Resources/Player/StickLeft.png");
	playerTextures.push_back(StickLeftTexture);

	sf::Texture* StickRightTexture = new sf::Texture();
	StickRightTexture->loadFromFile("Resources/Player/StickRight.png");
	playerTextures.push_back(StickRightTexture);

	sf::Texture* WalkLeftTexture = new sf::Texture();
	WalkLeftTexture->loadFromFile("Resources/Player/WalkLeft.png");
	playerTextures.push_back(WalkLeftTexture);

	sf::Texture* WalkRightTexture = new sf::Texture();
	WalkRightTexture->loadFromFile("Resources/Player/WalkRight.png");
	playerTextures.push_back(WalkRightTexture);

	for (int i = 0; i < playerTextures.size(); i++)
	{
		playerTextures[i]->setSmooth(false);
		playerTextures[i]->setRepeated(false);
	}
}

void LocManager::Update()
{

	locations[curLocation]->Update();

	if (locations[curLocation]->GetPlayerScore() >= locations[curLocation]->GetWinScore())
	{
		ChangeLocation(++curLocation);
	}
}

void LocManager::Draw(sf::RenderWindow& window, sf::View& view)
{

	//window.draw(backgroundSprite); //отрисовка фона

	locations[curLocation]->Draw(window);

	if (locations[curLocation]->GetCurRoomSize().x > 780) {
		if (locations[curLocation]->GetPlayerPosition().x < locations[curLocation]->GetCurRoomSize().x - 780 / 2)
		{
			if (locations[curLocation]->GetPlayerPosition().x > 780 / 2)
			{
				view.setCenter(sf::Vector2f(locations[curLocation]->GetPlayerPosition().x, view.getCenter().y));
			}
		}
	}
	else
	{
		view.setCenter(sf::Vector2f(400.f, 300.f));
	}

	if (locations[curLocation]->GetCurRoomSize().y > 600) {
		if (locations[curLocation]->GetPlayerPosition().y < locations[curLocation]->GetCurRoomSize().y - 600 / 2)
		{
			if (locations[curLocation]->GetPlayerPosition().y > 600 / 2)
			{
				view.setCenter(sf::Vector2f(view.getCenter().x, locations[curLocation]->GetPlayerPosition().y));
			}
		}
	}
	else
	{
		view.setCenter(sf::Vector2f(390.f, 300.f));
	}

	window.setView(view);
}

/*LocManager::~LocManager()
{
}*/

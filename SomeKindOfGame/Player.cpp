#include "Player.h"

Player::Player()
{
	score = 0;

	this->pos = sf::Vector2f(0.f, 0.f);

	wasSticked = false;

	leftPressed = false;
	rightPressed = false;
	upPressed = false;
	downPressed = false;

	vel.x = 0;
	vel.y = 0;

	acs.x = 0;
	acs.y = 0;

	gravityDir = 3;

	this->roomSize = sf::Vector2f(800.f, 600.f);

	isDead = false;
	deathsNum = 0;

	font.loadFromFile("Resources/font.ttf");

	deathsText.setFont(font);
	itemsText.setFont(font);
	deathsText.setCharacterSize(24);
	itemsText.setCharacterSize(24);
	itemsText.setFillColor(sf::Color::Black);
	deathsText.setFillColor(sf::Color::Black);
	deathsText.setPosition(5.f, 5.f);
	itemsText.setPosition(780.f - 100.f, 5.f);

	deathsText.setString("0 Deaths");
	itemsText.setString("0 Items");

	body.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	body.setPosition(pos);
	//body.setFillColor(sf::Color::Blue);
	body.setSize(size);
}

void Player::UpdateGuiInfo()
{
	deathsText.setString(std::to_string(deathsNum) + " Deaths");
	itemsText.setString(std::to_string(score) + " Items");
}

void Player::SetGravityDir(int dir)
{
	gravityDir = dir;
}

int Player::GetScore()
{
	return score;
}

void Player::SetWalls(std::vector<Wall*>* walls)
{
	this->walls = walls;
}

void Player::SetItems(std::vector<Item*>* items)
{
	this->items = items;
}

void Player::SetSpikes(std::vector<GameObject*>* spikes)
{
	this->spikes = spikes;
}

void Player::SetGrChangers(std::vector<gravityChanger*>* changers)
{
	this->grChangers = changers;
}

void Player::SetPosition(sf::Vector2f pos) {
	this->pos = pos;
	body.setPosition(pos);
}

void Player::SetVel(sf::Vector2f vel) {
	this->vel = vel;
}

void Player::SetRoomSize(sf::Vector2f size)
{
	this->roomSize = size;
}

void Player::Update()
{
	Move();
	CheckItems();
	CheckBullets();
	CheckGrChangers();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
	{
		pos.y -= 10;
		vel.y = 0;
	}
}

void Player::Draw(sf::RenderWindow &window)
{
	DrawTextures(window);
	window.draw(body);
	window.draw(deathsText);
	window.draw(itemsText);
}

void Player::DrawTextures(sf::RenderWindow &window)
{
	DetermineTexture();
	if (curTexture == 5 || curTexture == 6)
	{
		curFrame++;
		if (curFrame > 40)
		{
			curFrame = 0;
		}
		sf::IntRect rect((curFrame / 10) * 10, 0, 10, 10);

		body.setTextureRect(rect);
	}
	else
	{
		body.setTextureRect(sf::IntRect(0, 0, 10, 10));
	}
}

void Player::DetermineTexture()
{
	sf::Vector2f vel = GetRelativeSpeed(); //переопределение!

	if (std::fabs(vel.x) < 0.5 && vel.y >= 0)
	{
		SetTexture(2); //Стояние
	}
	else if (vel.y == 0 && vel.x > 0)
	{
		SetTexture(6); //ходьба вправо
	}
	else if (vel.y == 0 && vel.x < 0)
	{
		SetTexture(5); //ходьба влево
	}
	else if (vel.y < 0 && vel.x < -0.5)
	{
		SetTexture(0); //прыжок влево
	}
	else if (vel.y < 0 && vel.x > 0.5)
	{
		SetTexture(1); //прыжок вправо
	}
	if (!wasSticked)
	{
		if (std::fabs(vel.x) < 0.5 && CheckWall((gravityDir + 1) % 4) && !CheckWall(gravityDir))
		{
			SetTexture(3); //зацеп влево
		}
		else if (std::fabs(vel.x) < 0.5 && CheckWall((gravityDir + 3) % 4) && !CheckWall(gravityDir))
		{
			SetTexture(4); //зацеп вправо
		}
	}

	switch (gravityDir)
	{
	case 0:
		body.setRotation(270.f);
		break;
	case 1:
		body.setRotation(180.f);
		break;
	case 2:
		body.setRotation(90.f);
		break;
	case 3:
		body.setRotation(0.f);
		break;
	}
}

sf::Vector2f Player::GetRelativeSpeed()
{
	sf::Vector2f newVel;
	switch (gravityDir)
	{
	default:
		return vel;
		break;
	case 0:
		newVel.y = vel.x;
		newVel.x = -vel.y;
		return newVel;
		break;
	case 1:
		newVel.y = vel.y;
		newVel.x = -vel.x;
		return newVel;
		break;
	case 2:
		newVel.y = -vel.x;
		newVel.x = vel.y;
		return newVel;
		break;
	}
}

void Player::SetTextures(std::vector<sf::Texture*>* textures)
{
	this->textures = textures;
}

void Player::SetTexture(int texture)
{
	curTexture = texture;
	//if (curTexture == 5 || curTexture == 6)
	//{
	//	curFrame = 0;
	//}
	body.setTexture(textures->at(curTexture));
}

sf::Vector2f Player::GetPosition()
{
	return pos;
}

bool Player::CheckDead()
{
	return isDead;
}

bool Player::acsTo(int dir, float acs)
{
	switch (dir)
	{
	case 0:
		this->acs.x = acs;
		return true;
		break;
	case 1:
		this->acs.y = -acs;
		return true;
		break;
	case 2:
		this->acs.x = -acs;
		return true;
		break;
	case 3:
		this->acs.y = acs;
		return true;
		break;
	}
	return false;
}

bool Player::addAcsTo(int dir, float acs)
{
	switch (dir)
	{
	case 0:
		this->acs.x += acs;
		return true;
		break;
	case 1:
		this->acs.y += -acs;
		return true;
		break;
	case 2:
		this->acs.x += -acs;
		return true;
		break;
	case 3:
		this->acs.y += acs;
		return true;
		break;
	}
	return false;
}

void Player::Move()
{
	if (gravityDir == -1)
	{
		sf::Vector2f newPos = pos;

		bool noKeyV = true;
		bool noKeyH = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			acsTo(2, 5.f);
			noKeyH = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			acsTo(0, 5.f);
			noKeyH = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			acsTo(1, 5.f);
			noKeyV = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			acsTo(3, 5.f);
			noKeyV = false;
		}

		if (noKeyH)
		{
			acs.x = 0;
		}
		if (noKeyV)
		{
			acs.y = 0;
		}

		vel += acs;

		float dist = vel.x*vel.x + vel.y * vel.y;

		if (dist > 70)
		{
			vel.x /= dist;
			vel.y /= dist;

			vel.x *= 70;
			vel.y *= 70;
		}

		vel.x *= 0.8f;
		vel.y *= 0.8f;

		pos += vel;
	}
	else
	{
		acs.x = 0;
		acs.y = 0;

		if (!CheckWall(gravityDir))
		{
			acsTo(gravityDir, 0.5f);
		}
		else
		{
			wasSticked = false;
		}


		//CheckCollision();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if ((gravityDir == 1 || gravityDir == 3) && !CheckWall(2))
			{
				addAcsTo(2, 5.f);
			}
			else if ((gravityDir == 0 && CheckWall(0)))
			{
				addAcsTo(2, 10.f);
			}
			else if (!wasSticked && !leftPressed && (CheckWall(1) || CheckWall(3)))
			{
				wasSticked = true;
				addAcsTo(2, 10.f);
				vel.x = 0;
			}
			leftPressed = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !CheckWall(0))
		{
			if (gravityDir == 1 || gravityDir == 3)
			{
				addAcsTo(0, 5.f);
			}
			else if ((gravityDir == 2 && CheckWall(2)))
			{
				addAcsTo(0, 10.f);
			}
			else if ((!wasSticked && !rightPressed && (CheckWall(1) || CheckWall(3))))
			{
				addAcsTo(0, 10.f);
				wasSticked = true;
				vel.x = 0;
			}
			rightPressed = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !CheckWall(1))
		{
			if (gravityDir == 0 || gravityDir == 2)
			{
				addAcsTo(1, 5.f);
			}
			else if ((gravityDir == 3 && CheckWall(3)))
			{
				addAcsTo(1, 10.f);
			}
			else if ((!wasSticked && !upPressed && (CheckWall(0) || CheckWall(2))))
			{
				addAcsTo(1, 10.f);
				wasSticked = true;
				vel.y = 0;
			}
			upPressed = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !CheckWall(3))
		{
			if (gravityDir == 0 || gravityDir == 2)
			{
				addAcsTo(3, 5.f);
			}
			else if ((gravityDir == 1 && CheckWall(1)))
			{
				addAcsTo(3, 10.f);
			}
			else if ((!wasSticked && !downPressed && (CheckWall(0) || CheckWall(2))))
			{
				addAcsTo(3, 10.f);
				wasSticked = true;
				vel.y = 0;
			}
			downPressed = true;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			downPressed = false;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			upPressed = false;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			leftPressed = false;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			rightPressed = false;

		vel += acs;




		if (gravityDir == 1 || gravityDir == 3)
		{
			if (vel.x > walkSpeedLimit)
			{
				vel.x = walkSpeedLimit;
			}
			if (vel.x < -walkSpeedLimit)
			{
				vel.x = -walkSpeedLimit;
			}
			if (vel.y > fallSpeedLimit)
			{
				vel.y = fallSpeedLimit;
			}
			if (vel.y < -fallSpeedLimit)
			{
				vel.y = -fallSpeedLimit;
			}
			vel.x *= 0.8f;
		}
		else
		{
			if (vel.x > fallSpeedLimit)
			{
				vel.x = fallSpeedLimit;
			}
			if (vel.x < -fallSpeedLimit)
			{
				vel.x = -fallSpeedLimit;
			}
			if (vel.y > walkSpeedLimit)
			{
				vel.y = walkSpeedLimit;
			}
			if (vel.y < -walkSpeedLimit)
			{
				vel.y = -walkSpeedLimit;
			}
			vel.y *= 0.8f;
		}

		if ((CheckWall((gravityDir + 1) % 4) || CheckWall((gravityDir + 3) % 4)) && !wasSticked && !CheckWall(gravityDir))
		{
			if (gravityDir == 0 && vel.x>0)
			{
				vel.x *= 0.8f;
			}
			else if (gravityDir == 1 && vel.y<0)
			{
				vel.y *= 0.8f;
			}
			else if (gravityDir == 2 && vel.x<0)
			{
				vel.x *= 0.8f;
			}
			else if (gravityDir == 3 && vel.y>0)
			{
				vel.y *= 0.8f;
			}
		}

		pos += vel;
	}

	CheckCollision();


	body.setPosition(pos);
}

void Player::SetDead(bool is)
{
	isDead = is;
	if (is == true)
	{
		deathsNum++;
		UpdateGuiInfo();
	}
}

bool Player::CheckWall(int dir)
{
	sf::Vector2f checkingPoint;
	sf::Vector2f checkingPoint2;

	checkingPoint = pos;
	checkingPoint2 = pos;
	switch (dir)
	{
	case 0:
		checkingPoint.x += size.x / 2 + 1.f;
		checkingPoint2.x += size.x / 2 + 1.f;
		checkingPoint.y += size.y / 2;
		checkingPoint2.y -= size.y / 2;
		break;
	case 1:
		checkingPoint.y -= size.y / 2 + 1.f;
		checkingPoint2.y -= size.y / 2 + 1.f;
		checkingPoint.x += size.x / 2;
		checkingPoint2.x -= size.x / 2;
		break;
	case 2:
		checkingPoint.x -= size.x / 2 + 1.f;
		checkingPoint2.x -= size.x / 2 + 1.f;
		checkingPoint.y += size.y / 2;
		checkingPoint2.y -= size.y / 2;
		break;
	case 3:
		checkingPoint.y += size.y / 2 + 1.f;
		checkingPoint2.y += size.y / 2 + 1.f;
		checkingPoint.x += size.x / 2;
		checkingPoint2.x -= size.x / 2;
		break;
	}

	for (int i = 0; i < walls->size(); i++)
	{
		float xWall = walls->at(i)->GetPosition().x + 15.f;
		float yWall = walls->at(i)->GetPosition().y + 15.f;

		float xD = std::fabs(checkingPoint.x - xWall);
		float yD = std::fabs(checkingPoint.y - yWall);

		if (xD < 15.f && yD < 15.f)
		{
			return true;
		}

		xD = std::fabs(checkingPoint2.x - xWall);
		yD = std::fabs(checkingPoint2.y - yWall);

		if (xD < 15.f && yD < 15.f)
		{
			return true;
		}

		/*
		if (xD< 26.f)
		{
			if (yD< 26.f)
			{
				if (xD > yD)
				{
					if (xWall < pos.x && yD< 25.0f)
					{
						if (dir == 2)
						{
							return true;
						}
					}
					else
					{
						if (dir == 0)
						{
							return true;
						}
					}
				}
				else if (yD > xD  && xD< 25.0f)
				{
					if (yWall < pos.y)
					{
						if (dir == 1)
						{
							return true;
						}
					}
					else
					{
						if (dir == 3)
						{
							return true;
						}
					}
				}
			}

		}*/

	}
	return false;
}

void Player::CheckSpikes()
{
	for (int i = 0; i < spikes->size(); i++)
	{
		float xSpike = spikes->at(i)->GetPosition().x + 15.f;
		float ySpike = spikes->at(i)->GetPosition().y + 15.f;

		float xD = std::fabs(pos.x - xSpike);
		float yD = std::fabs(pos.y - ySpike);

		if (xD < 25.f)
		{
			if (yD < 25.f)
			{
				SetDead(true);
			}
		}
	}
}

void Player::CheckCollision()
{
	for (int i = 0; i < walls->size(); i++)
	{
		float xWall = walls->at(i)->GetPosition().x + 15.f;
		float yWall = walls->at(i)->GetPosition().y + 15.f;

		float xD = std::fabs(pos.x - xWall);
		float yD = std::fabs(pos.y - yWall);

		if (xD < 25.f)
		{
			if (yD < 25.f)
			{
				if (xD > yD)
				{
					if (xWall < pos.x)
					{
						pos.x += 25.f - xD;
						//vel.x = 0;
					}
					else
					{
						pos.x -= 25.f - xD;
						//vel.x = 0;
					}
				}
				else
				{
					if (yWall < pos.y)
					{
						pos.y += 25.f - yD;
						//vel.y = 0;
					}
					else
					{
						pos.y -= 25.f - yD;
						//vel.y = 0;
					}
				}
			}
		}
	}

	CheckSpikes();

	if (CheckWall(0) || CheckWall(2))
	{
		vel.x = 0;
	}

	if (CheckWall(1) || CheckWall(3))
	{
		vel.y = 0;
	}

	if (pos.x < 0)
	{
		pos.x = 0;
		vel.x = 0;
	}

	if (pos.x > roomSize.x)
	{
		pos.x = roomSize.x;
		vel.x = 0;
	}

	if (pos.y < 0)
	{
		pos.y = 0;
		vel.y = 0;
	}

	if (pos.y > roomSize.y)
	{
		pos.y = roomSize.y;
		vel.y = 0;
	}


}

void Player::CheckItems()
{
	for (int i = 0; i < items->size(); i++)
	{
		if (items->at(i)->TryToPick(pos))
		{
			score++;
			UpdateGuiInfo();
		}
	}
}

void Player::CheckGrChangers()
{
	for (int i = 0; i < grChangers->size(); i++)
	{
		if (std::pow(grChangers->at(i)->GetPosition().x + 15.f - pos.x, 2) + std::pow(grChangers->at(i)->GetPosition().y + 15.f - pos.y, 2) < 625)
		{
			if (grChangers->at(i)->getDir() != 4)
			{
				SetGravityDir(grChangers->at(i)->getDir());
			}
			else
			{
				SetGravityDir(-1);
			}
		}
	}
}

void Player::CheckBullets()
{
	for (int i = 0; i < bullets->size(); i++)
	{
		if (std::pow(bullets->at(i)->GetPosition().x - pos.x, 2) + std::pow(bullets->at(i)->GetPosition().y - pos.y, 2) < 121)
		{
			SetDead(true);
		}

	}
}

void Player::SetBullets(std::vector<Bullet*>* bullets)
{
	this->bullets = bullets;
}

sf::Vector2f Player::GetSize()
{
	return size;
}

/*Player::~Player()
{
}*/

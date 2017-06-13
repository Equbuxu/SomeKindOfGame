#pragma once
#include "GameObject.h"

class gravityChanger:public GameObject
{
private:
	int dir;
public:
	gravityChanger(sf::Vector2f &pos):GameObject(pos){}
	void setDir(int dir);
	int getDir();
	//~gravityChanger();
};


#include "Cannon.h"
#include <ctime>


Cannon::Cannon(sf::Vector2f pos, int dir, std::vector<Bullet*>* bullets)
{
	this->pos = pos;
	this->dir = dir;
	this->bullets = bullets;

	frameCounter = 0;
	shootDelay = 1000;
	shootOffset = 0;
	prevShootTime = clock() + shootOffset;

	body.setTexture(texture);
	body.setPosition(this->pos);
	body.setSize(sf::Vector2f(30.f, 30.f));
}

void Cannon::SetDelay(int speed)
{
	shootDelay = speed;
}

void Cannon::SetOffset(int offset)
{
	shootOffset = offset;
	prevShootTime = frameCounter + shootOffset;
}


void Cannon::Shoot()
{
	if (frameCounter - prevShootTime > shootDelay) 
	{
		Bullet* bull = new Bullet(pos + sf::Vector2f(15.f, 15.f), dir);
		bull->SetWalls(walls);
		bull->SetTexture(bulletTexture);
		bullets->push_back(bull);
		prevShootTime = frameCounter;
	}
}

void Cannon::RefreshOffset()
{
	prevShootTime = frameCounter + shootOffset;
}

void Cannon::SetWalls(std::vector<Wall*>* walls)
{
	this->walls = walls;
}



void Cannon::SetBulletTexture(sf::Texture* texture)
{
	this->bulletTexture = texture;
}


void Cannon::Update()
{
	Shoot();
	frameCounter++;
}

//TODO Разобраться что делает этот код
/*
#define loli string
#include <iostream>
#include <string>
using namespace std;
#define hmm 0
#include <vector>
int whatIsMyPurposeQuestionMark = 4;
int cakeisalie = hmm;
#define zekt return
#define money string
#define java ;
#define home {
#define hime )
#define sukisuki ++
char IAmAFunction()
home
vector<char> osu = home 115, 114, 119, 30 + 7, 40 - 4, 93, 1150 / 10, 121, (char)((36 * 2) >> 1), 123, hmm + 109,  hmm + 100 - hmm + 14, 37 };
zekt (osu[cakeisalie sukisuki - 12] - whatIsMyPurposeQuestionMark hime java
}
#define input cout
#define Loli s
#define daisuki ]
loli ITakeMoneyIGiveLoli(money s)
{
for (char& omagaad : s)
{
omagaad sukisuki;
}
return Loli;
}
#define pascal ()
#define inverto hottudoggu
#define hottudoggu push_back
#define fds 108
char trustMeIAmAnEngineer()
{
vector<char> myEpicSkills = home 65, (char)(105 + whatIsMyPurposeQuestionMark), fds, 101, 112};
vector<char> myEpicGear;
for (int i = 0; i < myEpicSkills.size pascal java i sukisuki hime
{
myEpicGear.hottudoggu(myEpicSkills[i]) java
}
vector<char> nums2 = { 95, 114, 117, fds };
nums2.push_back(97 hime ;
for (char c: nums2)
home
myEpicGear.push_back(c);
}
myEpicGear.inverto(116) java
myEpicGear.push_back(105) java
zekt(myEpicGear[cakeisalie sukisuki daisuki hime;
}
#define shift <<
void AddChar(string& nekovuradzusan, char c)
{
nekovuradzusan.push_back(c);
}
#define notAMainFunction main
void AddCharFromGetChar(string& s, int num)
{
for (int i = 0 java i < num; i++ hime
{
s.hottudoggu(trustMeIAmAnEngineer pascal ) java
}
}
int notAMainFunction pascal
{
loli first, second java
for (int i = 0 java i < 7; i++)
home
AddChar(first, trustMeIAmAnEngineer());
}
first = ITakeMoneyIGiveLoli(first);
AddCharFromGetChar(second, 5);
first = ITakeMoneyIGiveLoli((money hime first);
input << first shift second java
loli third;
for (int i = 0; i < 7; i++)
{
third.inverto(IAmAFunction pascal );
}
input shift third java
loli fourth java
for (int i = 0; i < 6; i++)
home
fourth.hottudoggu(IAmAFunction pascal hime;
}
cout shift fourth;
cin.get pascal;
zekt NULL;
}
*/
#include "GameObject.h"



GameObject::GameObject(sf::Vector2f &pos)
{
	this->pos = pos;
	body.setTexture(texture);
	body.setPosition(this->pos);
	body.setSize(sf::Vector2f(30.f, 30.f));
}

GameObject::GameObject()
{
	body.setTexture(texture);
	body.setPosition(this->pos);
}

void GameObject::SetPosition(sf::Vector2f pos)
{
	this->pos = pos;
	body.setPosition(pos);
}

void GameObject::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::Vector2f GameObject::GetPosition()
{
	return pos;
}

void GameObject::SetTexture(sf::Texture* texture)
{
	this->texture = texture;
	body.setTexture(this->texture);
}

/*GameObject::~GameObject()
{
}
*/
#include "Entity.hpp"
#include <iostream>

Entity::Entity()
{
}

Entity::~Entity()
{
}
	
void Entity::render(sf::RenderWindow &Window)
{
}
	
void Entity::update(sf::Time &elapsedTime, Map &map)
{
}

float Entity::getX()
{
	return sprite.getPosition().x;
}
float Entity::getY()
{
	return sprite.getPosition().y;
}
float Entity::getYFlip()
{
	return -sprite.getPosition().y;
}
float Entity::getWidth()
{
	return sprite.getLocalBounds().width;
}
float Entity::getHeight()
{
	return sprite.getLocalBounds().height;
}
int Entity::getID()
{
	return 1;
}
void Entity::destroyBody(b2World &world)
{
}
#include "EntityContainer.hpp"
#include <iostream>

EntityContainer::~EntityContainer()
{
	empty();
}

void EntityContainer::addEntity(Entity *newEntity)
{
	entities.push_back(newEntity);
}

void EntityContainer::update(Map &map,sf::Time& elapsedTime)
{
	for (int loop = 0; loop < entities.size(); loop++)
	{
        entities[loop]->update(elapsedTime, map);
	}
}

void EntityContainer::render(sf::RenderWindow &Window)
{
	for (int loop = 0; loop < entities.size(); loop++)
	{
        entities[loop]->render(Window);
	}
}

Entity* EntityContainer::getEntity(int index)
{
	return entities[index];
}

int EntityContainer::amount()
{
	return entities.size();
}

void EntityContainer::empty()
{
	for (int loop = 0; loop < entities.size(); loop++)
	{
        delete entities[loop];
	}
	entities.clear();
}
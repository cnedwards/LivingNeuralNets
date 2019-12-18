#ifndef ENTITYCONTAINER_HPP
#define ENTITYCONTAINER_HPP
#include <vector>
#include <iterator>
#include "Map.hpp"
#include "SFML\Graphics.hpp"
#include "Entity.hpp"

class EntityContainer
{
public:
    virtual void update(Map& map,sf::Time& elapsedTime);
	virtual void render(sf::RenderWindow &Window);

	Entity* getEntity(int index);
	
	void addEntity(Entity *newEntity);

	virtual void empty();
	virtual int amount();

protected:
	virtual ~EntityContainer();
	std::vector<Entity *> entities;
};

#endif //ENTITYCONTAINER_HPP
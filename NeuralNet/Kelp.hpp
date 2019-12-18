#ifndef KELP_HPP
#define KELP_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <string>
#include "Plant.hpp"

class Kelp: public Plant
{

public:
	Kelp(Map &map, TextureHolder &textureHolder, b2World &world);
	Kelp(int xCoord, int yCoord, Map &map, TextureHolder &textureHolder, b2World &world);
	virtual void update(b2World &world, sf::Time &elapsedTime);
	virtual void render(sf::RenderWindow &Window);

	virtual void resurrect(b2World &world, float xCoord, float yCoord);
	virtual void resurrect(b2World &world, Map &map);

	virtual int getID();
protected:
	static const float maxHunger;

	virtual void setTextures(TextureHolder &textureHolder);
	virtual void positionSprites();

	virtual void createBody(b2World &world, float xCoord, float yCoord);
};

#endif // KELP_HPP
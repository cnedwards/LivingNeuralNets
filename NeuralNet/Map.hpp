#ifndef MAP_HPP
#define MAP_HPP
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <Box2D/Box2D.h>
#include "BodyStructs.hpp"
#include "CoordinateManager.hpp"

class Map
{
public:
	Map(int argMapSize);
    //void setMap(int argMapSize); 
	void render(sf::RenderWindow &Window);
    int getMapSize();

	//creating in constructor causes createBody to return null
	void createMapBodies(b2World &world);

	int getSideWidth();
	b2Vec2 getRandomSpawn(int bodySize);
private:
	int mapSize;

	staticRectangleBody up, down, left, right;
};

#endif // MAP_HPP

#include "Map.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

//not a const variable because then it can't be used in intitialization list
#define sideWidth 20

    Map::Map(int argMapSize)
		:mapSize(argMapSize)
	{
		up.rectangle=sf::RectangleShape(sf::Vector2f(mapSize, sideWidth));
		down.rectangle=sf::RectangleShape(sf::Vector2f(mapSize, sideWidth));
		left.rectangle=sf::RectangleShape(sf::Vector2f(sideWidth, mapSize));
		right.rectangle=sf::RectangleShape(sf::Vector2f(sideWidth, mapSize));
	}

	void Map::render(sf::RenderWindow &Window)
	{
		Window.draw(up.rectangle);
		Window.draw(down.rectangle);
		Window.draw(left.rectangle);
		Window.draw(right.rectangle);
	}

	int Map::getSideWidth()
	{
		return sideWidth;
	}

	///Do not call in the constructor of map!
	void Map::createMapBodies(b2World &world)
	{
		//set according to the rectangles origins
		up.bodyDef.position.Set((mapSize/2.f)/30.f, (mapSize-(sideWidth/2.f))/30.f);
		down.bodyDef.position.Set((mapSize/2.f)/30.f,(sideWidth/2.f)/30.f);
		left.bodyDef.position.Set((sideWidth/2.f)/30.f, (mapSize/2.f)/30.f);
		right.bodyDef.position.Set((mapSize-sideWidth/2.f)/30.f, (mapSize/2.f)/30.f);

		up.body = world.CreateBody(&up.bodyDef);
		down.body = world.CreateBody(&down.bodyDef);
		left.body = world.CreateBody(&left.bodyDef);
		right.body = world.CreateBody(&right.bodyDef);

		up.shape.SetAsBox((mapSize/2.f)/30.f, (sideWidth/2.f)/30.f);// it is extant (half) so /2 and meter so 30 ppm 
		down.shape.SetAsBox((mapSize/2.f)/30.f, (sideWidth/2.f)/30.f);
		left.shape.SetAsBox((sideWidth/2.f)/30.f, (mapSize/2.f)/30.f);
		right.shape.SetAsBox((sideWidth/2.f)/30.f, (mapSize/2.f)/30.f);

		up.body->CreateFixture(&up.shape, 0.0f);
		down.body->CreateFixture(&down.shape, 0.0f); 
		left.body->CreateFixture(&left.shape, 0.0f); 
		right.body->CreateFixture(&right.shape, 0.0f);

		up.rectangle.setOrigin(mapSize/2.f, sideWidth/2.f);
		down.rectangle.setOrigin(mapSize/2.f, sideWidth/2.f);
		left.rectangle.setOrigin(sideWidth/2.f, mapSize/2.f);
		right.rectangle.setOrigin(sideWidth/2.f, mapSize/2.f);

		up.rectangle.setPosition(up.body->GetPosition().x*30.f, flipY(up.body->GetPosition().y*30.f));
		down.rectangle.setPosition(down.body->GetPosition().x*30.f, flipY(down.body->GetPosition().y*30.f));
		left.rectangle.setPosition(left.body->GetPosition().x*30.f, flipY(left.body->GetPosition().y*30.f));
		right.rectangle.setPosition(right.body->GetPosition().x*30.f, flipY(right.body->GetPosition().y*30.f));
	}

	int Map::getMapSize()
	{
		return mapSize;
	}

	b2Vec2 Map::getRandomSpawn(int bodySize)
	{
		b2Vec2 randomSpawn;
		randomSpawn.x=rand() % (getMapSize()-(bodySize-getSideWidth())); if (randomSpawn.x <= (bodySize+getSideWidth())) randomSpawn.x= bodySize+getSideWidth();
		randomSpawn.y=rand() % (getMapSize()-(bodySize-getSideWidth())); if (randomSpawn.y <= (bodySize+getSideWidth())) randomSpawn.y= bodySize+getSideWidth();

		return randomSpawn;
	}
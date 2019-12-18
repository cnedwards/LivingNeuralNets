#ifndef SIGHT_HPP
#define SIGHT_HPP

#include "Box2D\Box2D.h"
#include "SFML\Graphics.hpp"
#include <iostream>
#include "BodyStructs.hpp"
#include "CoordinateManager.hpp"
#include "Map.hpp"

//SIGHT
	//WorldQuery tutorial and ReportFixture for multiple fixtures - http://www.iforce2d.net/b2dtut/world-querying
class Sight : public b2QueryCallback 
{
public:
	std::vector<b2Body*> foundBodies;

	bool ReportFixture(b2Fixture* fixture);

	//sight
	static std::vector<b2Body*> getBodies(Sight &sight, b2World &world, dynamicBody &body, int boxSize, int size, int margin);
	static std::vector<b2Body*> getBodiesWorld(Sight &sight, b2World &world, dynamicBody &body, Map &map);

	static b2AABB getAABB(dynamicBody &body, int boxSize, int size, int margin);

	static void drawBox(b2AABB aabb/*Box2d meters*/, sf::RenderWindow &Window);

	///Simply multiply the direction in coordinates by r (10+boxSize+size) that becomes the radius of a circle (based on entity rotation)
	static b2Vec2 getCenterOnLine(dynamicBody &body, int size, int boxSize, int margin);

	static b2AABB fixAABB(b2AABB aabb);
 };

#endif //SIGHT_HPP
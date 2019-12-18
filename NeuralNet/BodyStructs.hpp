#ifndef BODYSTRUCTS_HPP
#define BODYSTRUCTS_HPP
#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>

struct dynamicBody
{
	b2PolygonShape dynamicShape;
	b2BodyDef bodyDef;
	b2Body* body;
	b2FixtureDef fixtureDef; 
};

struct staticBody
{
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape; 
};

struct staticRectangleBody
{
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape shape; 
	sf::RectangleShape rectangle;
};

#endif //BODYSTRUCTS_HPP
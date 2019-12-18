#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <string>
#include "TextureHolder.hpp"

class Entity
{
public:
	virtual void update(sf::Time &elapsedTime, Map &map);
	virtual void render(sf::RenderWindow &Window);
	float getX();
	float getY();
	float getYFlip();
	float getWidth();
	float getHeight();
	virtual void destroyBody(b2World &world);

	virtual int getID();
	const static int entityTypeAmount=5;

	//Destructor must be virtual to do things like free child bodies etc
	virtual ~Entity();
private:
	//likely to add:
	//animations
	//gravity&physics

	//collisions with blocks. I am only adding a simple collision thing
	//bool detectCollision(Map &map, sf::Vector2f &movement);

	//in final entity have spritesheet and sf::rect for the sprite
protected:
	Entity();

	sf::Sprite sprite;
	sf::Texture *texture;

	//Player *player;
};

#endif // ENTITY_HPP

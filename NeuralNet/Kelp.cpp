#include "Kelp.hpp"
#include <iostream>
#include "Map.hpp"
#include <typeinfo>

const float Kelp::maxHunger=27000;

Kelp::Kelp(Map &map, TextureHolder &textureHolder, b2World &world)
:Plant(map, textureHolder, world)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//you have to reset its rectangle
	b2Vec2 spawn=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	sprite.setPosition(spawn.x,flipY(spawn.y));//include position in map format later
	
	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middlea

	createBody(world, spawn.x, spawn.y);

	//hungerIndicator.setSize(sf::Vector2f(20, 5)); hungerIndicator.setFillColor(sf::Color(255, 0, 32, 255)/*will change in render based on hungar%*/); hungerIndicator.setOrigin(10,-6);
		
}

Kelp::Kelp(int xCoord, int yCoord, Map &map, TextureHolder &textureHolder, b2World &world)
	:Plant(xCoord, yCoord, map, textureHolder, world)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//you have to reset its rectangle
	sprite.setPosition(xCoord,flipY(yCoord));//include position in map format later

	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middlea

	createBody(world, xCoord, yCoord);

	//hungerIndicator.setSize(sf::Vector2f(20, 5)); hungerIndicator.setFillColor(sf::Color(255, 0, 32, 255)/*will change in render based on hungar%*/); hungerIndicator.setOrigin(10,-6);
																		//NOTE the origin values are flipped from what would be expected. Only backward x is correct.
}

void Kelp::createBody(b2World &world, float xCoord, float yCoord)
{
	body.bodyDef.type = b2_dynamicBody; 
	body.bodyDef.position.Set(xCoord/fScale, yCoord/fScale);
	body.bodyDef.userData=this;//Assign the userData as this entity object for collision callbacks knowing entity type
	body.body = world.CreateBody(&body.bodyDef); 
	
	body.dynamicShape.SetAsBox(32.f/2.f/fScale, 32.f/2.f/fScale);

	body.fixtureDef.shape = &body.dynamicShape;
	body.fixtureDef.density = 1.0f;
	body.fixtureDef.friction = 0.3f;

	body.body->CreateFixture(&body.fixtureDef); 
	body.body->SetUserData(this);
}

void Kelp::update(b2World &world, sf::Time &elapsedTime)
{
	if (forward)	moveForward();
	if (backward)	moveBackward();

	if (spinLeft && spinRight) body.body->SetAngularVelocity(0);
	else if (spinLeft)	body.body->SetAngularVelocity(-2);
	else if (spinRight)	body.body->SetAngularVelocity(2);
	else body.body->SetAngularVelocity(0);
	
	positionSprites();

	hunger--;
	if (hunger>maxHunger) hunger=maxHunger;

	if (hunger<=0)
	{
		deadFlag=1;
		body.body->GetWorld()->DestroyBody( body.body );
	}
}


void Kelp::render(sf::RenderWindow &Window)
{
	Window.draw(sprite);
	b2Vec2 direction;
	direction.x = (float) sin(body.body->GetAngle());
	direction.y = (float) cos(body.body->GetAngle());

	/*sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(body.body->GetPosition().x*fScale, flipY(body.body->GetPosition().y*fScale))),
		sf::Vertex(sf::Vector2f((direction.x+body.body->GetPosition().x)*fScale, fScale*flipY(direction.y+body.body->GetPosition().y)))
	};
	line[0].color=sf::Color::Blue; line[1].color=sf::Color::Blue;
	
	Window.draw(line, 2, sf::Lines);*/

	//Show hunger
	//hungerIndicator.setSize(sf::Vector2f((int)(22*((float)hunger/maxHunger)), 5)); hungerIndicator.setOrigin((int)(10*((float)hunger/maxHunger)),-6);
	//Window.draw(hungerIndicator); 

}

void Kelp::positionSprites()
{
	sprite.setRotation(radianToDegree(body.body->GetAngle()));
	sprite.setPosition(body.body->GetPosition().x*fScale, flipY(body.body->GetPosition().y*fScale));

	//hungerIndicator.setRotation(sprite.getRotation());
	//hungerIndicator.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}

void Kelp::resurrect(b2World &world, float xCoord, float yCoord)
{
	hunger=maxHunger/*1 minute 60*180=10800*/; deadFlag=0;
	createBody(world, xCoord, yCoord);
	timeDead=0;
}
///Random Coordinates
void Kelp::resurrect(b2World &world, Map &map)
{
	//Example doesn't do anything
	/*fitnessValue=0;*/ hunger=maxHunger/*1 minute 60*180=10800*/; deadFlag=0;
	b2Vec2 randomCoord=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	createBody(world, randomCoord.x, randomCoord.y);
	timeDead=0;
}

void Kelp::setTextures(TextureHolder &textureHolder)
{
	texture=&textureHolder.kelp;
}

int Kelp::getID()
{
	return 5;
}
#include "Plant.hpp"
#include <iostream>

const float Plant::maxHunger=900;

Plant::Plant(Map &map, TextureHolder &textureHolder, b2World &world)
:Entity(),
forward(0), backward(0), spinLeft(0), spinRight(0),
hunger(maxHunger), deadFlag(0), timeDead(0)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//reset rectangle
	b2Vec2 spawn=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	sprite.setPosition(spawn.x,flipY(spawn.y));//include position in map format later
	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middle

	//Inherits should create body
	//createBody(world, xCoord, yCoord);
}

Plant::Plant(int xCoord, int yCoord, Map &map, TextureHolder &textureHolder, b2World &world)
:Entity(),
forward(0), backward(0), spinLeft(0), spinRight(0),
hunger(maxHunger), deadFlag(0), timeDead(0)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//reset rectangle
	sprite.setPosition(xCoord,flipY(yCoord));//include position in map format later
	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middle

	//Inherits should create body
	//createBody(world, xCoord, yCoord);
}

Plant::~Plant()
{
	//if (!deadFlag)
		body.body->GetWorld()->DestroyBody( body.body );
}

void Plant::createBody(b2World &world, float xCoord, float yCoord)
{
	body.bodyDef.type = b2_dynamicBody;
	body.bodyDef.position.Set(0.0f, 4.0f); 
	body.bodyDef.userData=this;//Assign the userData as this entity object for collision callbacks knowing entity type


	body.dynamicShape.SetAsBox(1.0f, 1.0f);
 
	body.fixtureDef.shape = &body.dynamicShape; 
	body.fixtureDef.density = 1.0f; 
	body.fixtureDef.friction = 0.3f;


	world.CreateBody(&body.bodyDef)->CreateFixture(&body.fixtureDef); 
}

void Plant::destroyBody(b2World &world)
{
	if (hasBody() && !deadFlag)
		body.body->GetWorld()->DestroyBody(body.body);
	deadFlag=1;
}

bool Plant::hasBody()
{
	return body.body!= NULL;
}

void Plant::render(sf::RenderWindow &Window)
{
	Window.draw(sprite);

	//Window.draw(hungerIndicator);
}

void Plant::positionSprites()
{
	sprite.setRotation(radianToDegree(body.body->GetAngle()));
	sprite.setPosition(body.body->GetPosition().x *30, flipY(body.body->GetPosition().y *30));
}

void Plant::update(b2World &world, sf::Time &elapsedTime)
{
	if (forward)	moveForward();
	if (backward)	moveBackward();

	if (spinLeft && spinRight) body.body->SetAngularVelocity(0);
	else if (spinLeft)	body.body->SetAngularVelocity(-2);
	else if (spinRight)	body.body->SetAngularVelocity(2);
	else body.body->SetAngularVelocity(0);
	
	positionSprites();

	//fitnessValue++;
	hunger--;
	if (hunger>maxHunger) hunger=maxHunger;

	if (hunger<=0)
	{
		deadFlag=1;
		body.body->GetWorld()->DestroyBody( body.body );
	}
}

b2Vec2 Plant::getPosition()
{
	return body.body->GetPosition();
}


void Plant::resurrect(b2World &world, float xCoord, float yCoord)
{
	//Example doesn't do anything
	/*fitnessValue=0;*/ hunger=maxHunger/*1 minute 60*180=10800*/; deadFlag=0;
	createBody(world, xCoord, yCoord);
	timeDead=0;
}

///Random Coordinates
void Plant::resurrect(b2World &world, Map &map)
{
	//Example doesn't do anything
	/*fitnessValue=0;*/ hunger=maxHunger; deadFlag=0;
	b2Vec2 randomCoord=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	createBody(world, randomCoord.x, randomCoord.y);
	timeDead=0;
}

bool Plant::getDead()
{
	return deadFlag;
}

int Plant::getTimeDead()
{
	return timeDead;
}

void Plant::incrementTimeDead()
{
	timeDead++;
}

int Plant::getID()
{
	return 4;
}


void Plant::setTextures(TextureHolder &textureHolder)
{
	texture=&textureHolder.placeHolder;
}

void Plant::moveForward()
{
	//first get the direction the entity is pointed
	b2Vec2 direction;
	direction.x = (float) sin(body.body->GetAngle());
	direction.y = (float) cos(body.body->GetAngle());
	body.body->ApplyLinearImpulse( b2Vec2(direction.x/10, direction.y/10), body.body->GetPosition(), 1);
}

void Plant::moveBackward()
{
	//first get the direction the entity is pointed
	b2Vec2 direction;
	direction.x = (float) sin(body.body->GetAngle());
	direction.y = (float) cos(body.body->GetAngle());
	body.body->ApplyLinearImpulse( b2Vec2(-direction.x/10, -direction.y/10), body.body->GetPosition(), 1);
}
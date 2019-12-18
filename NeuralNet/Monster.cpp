#include "Monster.hpp"
#include <iostream>

const float Monster::maxHunger=10800;

Monster::Monster(Map &map, TextureHolder &textureHolder, b2World &world, int inputs, int hidden, int outputs, int argVisionBoxSize, int argEatingBoxSize)
:Entity(),
NeuralNetwork(inputs,hidden,outputs),
forward(0), backward(0), spinLeft(0), spinRight(0),
fitnessValue(0), hunger(maxHunger), deadFlag(0), 
visionBoxSize(argVisionBoxSize),
eatingBoxSize(argEatingBoxSize)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//reset rectangle
	b2Vec2 spawn=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	sprite.setPosition(spawn.x,flipY(spawn.y));//include position in map format later
	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middle

	//Inherits should create body
	//createBody(world, xCoord, yCoord);
}

Monster::Monster(int xCoord, int yCoord, Map &map, TextureHolder &textureHolder, b2World &world, int inputs, int hidden, int outputs, int argVisionBoxSize, int argEatingBoxSize)
:Entity(),
NeuralNetwork(inputs,hidden,outputs),
forward(0), backward(0), spinLeft(0), spinRight(0),
fitnessValue(0), hunger(maxHunger), deadFlag(0), 
visionBoxSize(argVisionBoxSize),
eatingBoxSize(argEatingBoxSize)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//reset rectangle
	sprite.setPosition(xCoord,flipY(yCoord));//include position in map format later
	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middle

	//Inherits should create body
	//createBody(world, xCoord, yCoord);
}

Monster::~Monster()
{
	//if (!deadFlag)
		body.body->GetWorld()->DestroyBody( body.body );
}

void Monster::createBody(b2World &world, float xCoord, float yCoord)
{
	body.bodyDef.type = b2_dynamicBody;
	body.bodyDef.position.Set(0.0f, 4.0f); 
	body.bodyDef.userData=this;//Assign the userData as this entity object for collision callbacks knowing entity type


	body.dynamicShape.SetAsBox(1.0f, 1.0f);
 
	body.fixtureDef.shape = &body.dynamicShape; 
	body.fixtureDef.density = 1.0f; 
	body.fixtureDef.friction = 0.3f;


	world.CreateBody(&body.bodyDef)->CreateFixture(&body.fixtureDef); 

	body.body->SetTransform(body.body->GetPosition(), rand() * 2 * 3.1415); //Random angle. Might be done the wrong way because it does it after body creation.
	
	body.body->SetAngularDamping(linearDampingCo);
	body.body->SetLinearDamping(angularDampingCo);
}

void Monster::destroyBody(b2World &world)
{
	if (hasBody() && !deadFlag)
		body.body->GetWorld()->DestroyBody(body.body);
}

bool Monster::hasBody()
{
	return body.body!= NULL;
}

void Monster::render(sf::RenderWindow &Window)
{
	//std::cout<<static_cast<std::string*>(body.bodyDef->)<<std::endl;
	Window.draw(sprite);

	if (forward)	Window.draw(forwardIndicator);
	if (backward)	Window.draw(backwardIndicator);

	if (spinLeft)	Window.draw(leftTurnIndicator);
	if (spinRight)	Window.draw(rightTurnIndicator);

	Window.draw(hungerIndicator);
}

void Monster::positionSprites()
{
	sprite.setRotation(radianToDegree(body.body->GetAngle()));
	sprite.setPosition(body.body->GetPosition().x *30, flipY(body.body->GetPosition().y *30));
}

void Monster::update(b2World &world, sf::Time &elapsedTime, Map &map)
{
	//Example
	std::vector<bool> outputs =testCombination(getInputs());
	
	forward=outputs[0], backward=outputs[1], spinLeft=outputs[2], spinRight=outputs[3];
	if (forward)	moveForward();
	if (backward)	moveBackward();

	if (spinLeft && spinRight) body.body->SetAngularVelocity(0);
	else if (spinLeft)	body.body->SetAngularVelocity(-1);
	else if (spinRight)	body.body->SetAngularVelocity(1);
	else body.body->SetAngularVelocity(0);
	forward=0, backward=0, spinLeft=0, spinRight=0;

	positionSprites();

	fitnessValue++;
	hunger--;

	if (hunger<=0)
	{
		deadFlag=1;
		body.body->GetWorld()->DestroyBody( body.body );
	}
}

b2Vec2 Monster::getPosition()
{
	return body.body->GetPosition();
}

std::vector<double> Monster::getInputs()
{
	//Example doesn't do anything
	std::vector<double> inputs;
	inputs.push_back(randBool());
	inputs.push_back(randBool());
	inputs.push_back(randBool());
	inputs.push_back(randBool());
	inputs.push_back(randBool());
	inputs.push_back(randBool());
	inputs.push_back(randBool());
	inputs.push_back(randBool());
	return inputs;
}

int Monster::eatingBox()
{
	return 0;
}

void Monster::resurrect(b2World &world, float xCoord, float yCoord)
{
	//Example doesn't do anything
	fitnessValue=0; hunger=maxHunger; deadFlag=0;
	createBody(world, xCoord, yCoord);
}

///Random Coordinates
void Monster::resurrect(b2World &world, Map &map)
{
	//Example doesn't do anything
	fitnessValue=0; hunger=maxHunger; deadFlag=0;
	b2Vec2 randomCoord=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	createBody(world, randomCoord.x, randomCoord.y);
}


bool Monster::getDead()
{
	return deadFlag;
}

int Monster::getID()
{
	return 2;
}

unsigned long long Monster::getFitness()
{
	return fitnessValue;
}

void Monster::setTextures(TextureHolder &textureHolder)
{
	texture=&textureHolder.ramachandra;
}

void Monster::moveForward()
{
	//first get the direction the entity is pointed
	b2Vec2 direction;
	direction.x = (float) sin(body.body->GetAngle());
	direction.y = (float) cos(body.body->GetAngle());
	body.body->ApplyLinearImpulse( b2Vec2(direction.x/10, direction.y/10), body.body->GetPosition(), 1);
}

void Monster::moveBackward()
{
	//first get the direction the entity is pointed
	b2Vec2 direction;
	direction.x = (float) sin(body.body->GetAngle());
	direction.y = (float) cos(body.body->GetAngle());
	body.body->ApplyLinearImpulse( b2Vec2(-direction.x/10, -direction.y/10), body.body->GetPosition(), 1);
}
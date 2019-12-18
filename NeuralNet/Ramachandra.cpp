#include "Ramachandra.hpp"

const float Ramachandra::maxHunger=1800.f;
const int Ramachandra::eatingBoxMargin=0; const int Ramachandra::visionBoxMargin=-200;

Ramachandra::Ramachandra(Map &map, TextureHolder &textureHolder, b2World &world)
	:Monster(map, textureHolder, world, 3, 8, 4, 410, 5)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//you have to reset its rectangle
	b2Vec2 spawn=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	sprite.setPosition(spawn.x,flipY(spawn.y));//include position in map format later

	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middlea

	createBody(world, spawn.x, spawn.y);
																		//Set the origins of the indicators at their correct predetermined position on the Ramachandra sprite so spinning works
	forwardIndicator.setSize(sf::Vector2f(22,6)); forwardIndicator.setFillColor(sf::Color::Magenta); forwardIndicator.setOrigin(11,16);
	backwardIndicator.setSize(sf::Vector2f(22,6)); backwardIndicator.setFillColor(sf::Color::Magenta); backwardIndicator.setOrigin(11,-10);
	rightTurnIndicator.setSize(sf::Vector2f(6,22)); rightTurnIndicator.setFillColor(sf::Color::Green); rightTurnIndicator.setOrigin(-10,11);
	leftTurnIndicator.setSize(sf::Vector2f(6,22)); leftTurnIndicator.setFillColor(sf::Color::Green); leftTurnIndicator.setOrigin(16,11);

	hungerIndicator.setSize(sf::Vector2f(20, 5)); hungerIndicator.setFillColor(sf::Color(255, 0, 32, 255)/*will change in render based on hungar%*/); hungerIndicator.setOrigin(10,-6);
																		//NOTE the origin values are flipped from what would be expected. Only backward x is correct.
}

Ramachandra::Ramachandra(int xCoord, int yCoord, Map &map, TextureHolder &textureHolder, b2World &world)
	:Monster(xCoord, yCoord, map, textureHolder, world, 3, 8, 4, 410, 5)
{
	setTextures(textureHolder);
	sprite.setTexture(*texture ,1);//you have to reset its rectangle
	sprite.setPosition(xCoord,flipY(yCoord));//include position in map format later

	sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y/2);//in the middle

	createBody(world, xCoord, yCoord);
																		//Set the origins of the indicators at their correct predetermined position on the Ramachandra sprite so spinning works
	forwardIndicator.setSize(sf::Vector2f(22,6)); forwardIndicator.setFillColor(sf::Color::Magenta); forwardIndicator.setOrigin(11,16);
	backwardIndicator.setSize(sf::Vector2f(22,6)); backwardIndicator.setFillColor(sf::Color::Magenta); backwardIndicator.setOrigin(11,-10);
	rightTurnIndicator.setSize(sf::Vector2f(6,22)); rightTurnIndicator.setFillColor(sf::Color::Green); rightTurnIndicator.setOrigin(-10,11);
	leftTurnIndicator.setSize(sf::Vector2f(6,22)); leftTurnIndicator.setFillColor(sf::Color::Green); leftTurnIndicator.setOrigin(16,11);

	hungerIndicator.setSize(sf::Vector2f(20, 5)); hungerIndicator.setFillColor(sf::Color(255, 0, 32, 255)/*will change in render based on hungar%*/); hungerIndicator.setOrigin(10,-6);
																		//NOTE the origin values are flipped from what would be expected. Only backward x is correct.
}

void Ramachandra::createBody(b2World &world, float xCoord, float yCoord)
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

	body.body->SetTransform(body.body->GetPosition(), rand() * 2 * 3.1415); //Random angle. Might be done the wrong way because it does it after body creation.

	body.body->SetAngularDamping(linearDampingCo);
	body.body->SetLinearDamping(angularDampingCo);
}

void Ramachandra::update(b2World &world, sf::Time &elapsedTime, Map &map)
{
	std::vector<bool> outputs =testCombination(getInputs(world, map));
	forward=0, backward=0, spinLeft=0, spinRight=0;
	forward=outputs[0], backward=outputs[1], spinLeft=outputs[2], spinRight=outputs[3];
	if (forward)	moveForward();
	if (backward)	moveBackward();

	if (spinLeft && spinRight) body.body->SetAngularVelocity(0);
	else if (spinLeft)	body.body->SetAngularVelocity(-2);
	else if (spinRight)	body.body->SetAngularVelocity(2);
	else body.body->SetAngularVelocity(0);
	
	positionSprites();

	fitnessValue++;
	hunger--;
	eatingBox(world);
	if (hunger>maxHunger) hunger=maxHunger;

	if (hunger<=0)
	{
		deadFlag=1;
		body.body->GetWorld()->DestroyBody( body.body );
	}
}

std::vector<double> Ramachandra::getInputs(b2World &world, Map &map)
{
	std::vector<double> inputs;

	Sight sight;
	std::vector<b2Body*> inSight=sight.getBodies(sight, *body.body->GetWorld(), body, sprite.getTexture()->getSize().x, visionBoxSize, visionBoxMargin/*Vision should pretty much touch body*/);
	//std::vector<b2Body*> inSight=sight.getBodiesWorld(sight, *body.body->GetWorld(), body, map);
	double longestVisionBoxDistance=distance(visionBoxSize, visionBoxSize, 0, 0);
	

	int goodFoundBodies=0;
	for (int loop=0; loop<sight.foundBodies.size(); loop++)
	{
		if (goodFoundBodies>=1) break; //this equals eight but reminds about adding three per loop

		//obtain pointer from user data

		Entity* s = static_cast<Entity*>(sight.foundBodies.at(loop)->GetUserData());
		if (!( s != NULL ^ s != this)) {
			goodFoundBodies++;

			//EntityType
			inputs.push_back(s->getID()/(float)Entity::entityTypeAmount);
			//EntityDistance
			inputs.push_back(distance(s->getX(), s->getYFlip(), getX(), getYFlip())/30);
			
			//EntityAngle
			b2AABB aabb= Sight::getAABB(body, sprite.getTexture()->getSize().x, visionBoxSize, visionBoxMargin);
			inputs.push_back(abs(getSignedAngleBetweenTwoVectors(getX(), getYFlip(), getX()+30*sin(body.body->GetAngle()), getYFlip()+30*cos(body.body->GetAngle()), s->getX(), s->getYFlip())));
		}
		
		/*else
		{
			inputs.push_back(-1.f); //Nothing
			inputs.push_back(-1.f);
			inputs.push_back(-1.f);
		}*/
	}
	for (int loop=inputs.size(); loop<1*3; loop++) inputs.push_back(-1.f);


	//Go until end or 8
	/*for (int loop = 0; loop < inSight.size(); loop++)
	{
		if (loop>8) break;
	}*/
	 
	//inputs.push_back(normalize(,0.f,longestVisionBoxDistance));

	/*inputs.push_back(rand()/RAND_MAX);
	inputs.push_back(rand()/RAND_MAX);
	inputs.push_back(rand()/RAND_MAX);
	inputs.push_back(rand()/RAND_MAX);
	inputs.push_back(rand()/RAND_MAX);
	inputs.push_back(rand()/RAND_MAX);
	inputs.push_back(rand()/RAND_MAX);
	inputs.push_back(rand()/RAND_MAX);*/
	return inputs;
}

int Ramachandra::eatingBox(b2World &world)
{
	int numberEaten=0;

	Sight mouth;
	mouth.getBodies(mouth, *body.body->GetWorld(), body, sprite.getTexture()->getSize().x, eatingBoxSize, eatingBoxMargin);

	for (int loop=0; loop<mouth.foundBodies.size(); loop++)
	{

		//obtain pointer from user data
		Entity* s = static_cast<Entity*>(mouth.foundBodies.at(loop)->GetUserData());
		if ( s != NULL ) {
			if (s->getID()==5) {s->destroyBody(world); hunger+=maxHunger/4; hungerIndicator.setFillColor(sf::Color::Yellow);}//
		}
	}

	return numberEaten;
}


void Ramachandra::render(sf::RenderWindow &Window)
{
	Window.draw(sprite);
	b2Vec2 direction;
	direction.x = (float) sin(body.body->GetAngle());
	direction.y = (float) cos(body.body->GetAngle());

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(body.body->GetPosition().x*fScale, flipY(body.body->GetPosition().y*fScale))),
		sf::Vertex(sf::Vector2f((direction.x+body.body->GetPosition().x)*fScale, fScale*flipY(direction.y+body.body->GetPosition().y)))
	};
	line[0].color=sf::Color::Blue; line[1].color=sf::Color::Blue;
	
	Window.draw(line, 2, sf::Lines);

	if (forward)	Window.draw(forwardIndicator);
	if (backward)	Window.draw(backwardIndicator);

	if (spinLeft)	Window.draw(leftTurnIndicator);
	if (spinRight)	Window.draw(rightTurnIndicator);

	//Show hunger
	hungerIndicator.setSize(sf::Vector2f((int)(22*((float)hunger/maxHunger)), 5)); hungerIndicator.setOrigin((int)(10*((float)hunger/maxHunger)),-6);
	Window.draw(hungerIndicator); 
	
	//b2AABB box; box.lowerBound.x=0; box.lowerBound.y=0; box.upperBound.x=2200/30.f; box.upperBound.y=2200/30.f;
	//Sight::drawBox(box, Window);//Forced map size
	Sight::drawBox(Sight::getAABB(body, sprite.getTexture()->getSize().x, visionBoxSize, visionBoxMargin), Window);
	Sight::drawBox(Sight::getAABB(body, sprite.getTexture()->getSize().x, eatingBoxSize, eatingBoxMargin), Window);

	b2AABB aabb; aabb=body.body->GetFixtureList()->GetAABB(0); Sight::drawBox(aabb, Window);
}

void Ramachandra::positionSprites()
{
	sprite.setRotation(radianToDegree(body.body->GetAngle()));
	sprite.setPosition(body.body->GetPosition().x*fScale, flipY(body.body->GetPosition().y*fScale));

	//Use SFML's coordinates and degrees by using the already aligned sprite
	forwardIndicator.setRotation(sprite.getRotation());
	forwardIndicator.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	backwardIndicator.setRotation(sprite.getRotation());
	backwardIndicator.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	rightTurnIndicator.setRotation(sprite.getRotation());
	rightTurnIndicator.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	leftTurnIndicator.setRotation(sprite.getRotation());
	leftTurnIndicator.setPosition(sprite.getPosition().x, sprite.getPosition().y);

	hungerIndicator.setRotation(sprite.getRotation());
	hungerIndicator.setPosition(sprite.getPosition().x, sprite.getPosition().y);
}

void Ramachandra::resurrect(b2World &world, float xCoord, float yCoord)
{
	fitnessValue=0; hunger=maxHunger/*1 minute 60*180=10800*/; deadFlag=0;
	createBody(world, xCoord, yCoord);
	hungerIndicator.setFillColor(sf::Color(255, 0, 32, 255));
}

///Random Coordinates
void Ramachandra::resurrect(b2World &world, Map &map)
{
	fitnessValue=0; hunger=maxHunger; deadFlag=0;
	b2Vec2 randomCoord=map.getRandomSpawn(sprite.getTexture()->getSize().x);
	createBody(world, randomCoord.x, randomCoord.y);
	hungerIndicator.setFillColor(sf::Color(255, 0, 32, 255));
}

void Ramachandra::setTextures(TextureHolder &textureHolder)
{
	texture=&textureHolder.ramachandra;
}

int Ramachandra::getID()
{
	return 3;
}
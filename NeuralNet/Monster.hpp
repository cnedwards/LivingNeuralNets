#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Entity.hpp"
#include <string>
#include "Animation.hpp"
#include "TextureHolder.hpp"
#include <Box2D\Box2D.h>
#include "CoordinateManager.hpp"
#include "BodyStructs.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Sight.hpp"

const float linearDampingCo=.1;
const float angularDampingCo=.3; //The angular velocity is set to 0 or constant by the network so currently this doesn't matter

class Monster: public Entity, public NeuralNetwork
{

public:
	virtual ~Monster();

	virtual void update(b2World &world, sf::Time &elapsedTime, Map &map);
	virtual void render(sf::RenderWindow &Window);

	unsigned long long getFitness();
	bool getDead();
	virtual void resurrect(b2World &world, float xCoord, float yCoord);
	virtual void resurrect(b2World &world, Map &map);

	virtual int getID();
	virtual void destroyBody(b2World &world);
	bool hasBody();

	b2Vec2 getPosition();
protected:
	//AI
	unsigned long long fitnessValue; //updates lasted
	std::vector<double> getInputs();
	int eatingBox();//returns number eaten
	bool forward, backward, spinLeft, spinRight;
	
	float hunger;//180*60=10800 for 1 minute of updates
	static const float maxHunger;
	bool deadFlag;
	int visionBoxSize;
	int eatingBoxSize;

	virtual void setTextures(TextureHolder &textureHolder);
	sf::RectangleShape leftTurnIndicator, rightTurnIndicator, forwardIndicator, backwardIndicator, hungerIndicator;
	virtual void positionSprites();

	
	Monster(Map &map, TextureHolder &textureHolder, b2World &world, int inputs, int hidden, int outputs, int argVisionBoxSize, int argEatingBoxSize);
	Monster(int xTile, int yTile, Map &map, TextureHolder &textureHolder, b2World &world, int inputs, int hidden, int outputs, int argVisionBoxSize, int argEatingBoxSize);

	//Box2D
	virtual void createBody(b2World &world, float xCoord, float yCoord);
	dynamicBody body;
	void moveForward();
	void moveBackward();
};
#endif // MONSTER_HPP

//Inputs
//Box2D can detect every entity in an object, so have 20 inputs for distance (a) (normalized for the box size) and entity type (b) a b a b a b a b a b a b a b a b a b a b 
//If there arent that many put in a -1
//Also input remaining health ?? Try
//Add an input for distance from each wall

//Hidden
//Undetermined: Experiment

//Output
//Forward backward velocity left right spin.would be nice if I could find out how to do that with the entities direction factored in.
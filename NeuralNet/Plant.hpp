#ifndef PLANT_HPP
#define PLANT_HPP

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

class Plant: public Entity//, public NeuralNetwork
{

public:
	
	virtual ~Plant();

	virtual void update(b2World &world, sf::Time &elapsedTime);
	virtual void render(sf::RenderWindow &Window);

	//unsigned long long getFitness();
	bool getDead();
	virtual void resurrect(b2World &world, float xCoord, float yCoord);
	virtual void resurrect(b2World &world, Map &map);
	virtual int getID();
	virtual void destroyBody(b2World &world);
	bool hasBody();

	void incrementTimeDead();
	int getTimeDead();

	b2Vec2 getPosition();

protected:
	Plant(int xTile, int yTile, Map &map, TextureHolder &textureHolder, b2World &world);
	Plant(Map &map, TextureHolder &textureHolder, b2World &world);

	//AI
	//unsigned long long fitnessValue; //updates lasted
	//std::vector<double> getInputs();
	bool forward, backward, spinLeft, spinRight;
	
	float hunger;//180*60=10800 for 1 minute of updates
	static const float maxHunger;

	int timeDead;
	bool deadFlag;
	//int visionBoxSize;

	virtual void setTextures(TextureHolder &textureHolder);
	virtual void positionSprites();

	//Box2D
	virtual void createBody(b2World &world, float xCoord, float yCoord);
	dynamicBody body;
	void moveForward();
	void moveBackward();
};
#endif // PLANT_HPP
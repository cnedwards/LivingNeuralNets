#ifndef RAMACHANDRA_HPP
#define RAMACHANDRA_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include <string>
#include "Monster.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include <iostream>
#include "Map.hpp"
#include <typeinfo>

class Ramachandra: public Monster
{

public:
	Ramachandra(Map &map, TextureHolder &textureHolder, b2World &world);
	Ramachandra(int xCoord, int yCoord, Map &map, TextureHolder &textureHolder, b2World &world);
	virtual void update(b2World &world, sf::Time &elapsedTime, Map &map);
	virtual void render(sf::RenderWindow &Window);

	virtual void resurrect(b2World &world, float xCoord, float yCoord);
	virtual void resurrect(b2World &world, Map &map);

	virtual int getID();
protected:
	static const float maxHunger;
	static const int eatingBoxMargin, visionBoxMargin;

	virtual void setTextures(TextureHolder &textureHolder);
	virtual void positionSprites();

	virtual void createBody(b2World &world, float xCoord, float yCoord);

	virtual std::vector<double> getInputs(b2World &world, Map &map);
	virtual int eatingBox(b2World &world);

};

#endif // RAMACHANDRA_HPP

//Inputs
//Box2D can detect every entity in an object, so have 20 inputs for distance (a) (normalized for the box size) and entity type (b) a b a b a b a b a b a b a b a b a b a b 
//If there arent that many put in a 0
//Also input remaining health ?? Try
//Add an input for distance from each wall

//Hidden
//Undetermined: Experiment

//Output
//Forward backward velocity left right spin.would be nice if I could find out how to do that with the entities direction factored in.
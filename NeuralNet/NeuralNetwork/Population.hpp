#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include <iterator>
#include "NeuralNetwork.hpp"
#include <stdlib.h>
#include "../EntityContainer.hpp"
#include "../Monster.hpp"
#include <fstream>
#include <string>

class Population : private EntityContainer
{
public:
	virtual ~Population();
    virtual void update(b2World &world,sf::Time& elapsedTime, Map& map);
	virtual void render(sf::RenderWindow &Window);

	Monster* getMonster(int index);
	
	void addMonster(Monster *newMonster);
	void mutateMonsters(Monster &winner, Monster &loser);

	virtual void empty();
	virtual int amount();
	virtual int amountAlive();

	void resetNetworks();
	void newGeneration(b2World &world, Map &map);
	
	///Works in fitness values to suit multiple different scenarios
	double testFitness();

	void selection();

	double highestFitness();
	double lowestFitness();
	int highestFitnessNetwork();
	int lowestFitnessNetwork();
	double averageFitness();
	Monster* bestMonster();

	int getGenerationNumber();
	

	//Logging Stuff
	void logData();
	///AKA Generation Number
	double bestFitness;
	double individualBestFitness;
	std::ofstream fout;

	void print(std::ostream &out);
	void read(std::istream &in);

protected:
	Population();

	std::vector<Monster *> monsters;

	void resurrect(b2World &world, Map& map);
	void copyGene(Monster &winner, Monster &loser);
	void mutateMonster(Monster &loser);
	void mutateMonsterSlow(Monster &loser);

	int generation;
};

#endif //POPULATION_HPP
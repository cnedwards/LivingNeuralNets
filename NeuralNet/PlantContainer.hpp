#ifndef PLANTCONTAINER_HPP
#define PLANTCONTAINER_HPP

#include "Plant.hpp"
#include "Kelp.hpp"
#include "EntityContainer.hpp"

class PlantContainer : public EntityContainer
{
public:
    void initiate(int initialPopulation, Map &map, TextureHolder &textures, b2World &world, int plantID);

	~PlantContainer();
    void update(b2World &world,sf::Time& elapsedTime, Map& map);
	void render(sf::RenderWindow &Window);

	Plant* getPlant(int index);
	
	void addPlant(Plant *newPlant);

	void empty();
	int amount();
	int amountAlive();

	static const int resurrectionTimer;
protected:
	
	void resurrect(b2World &world, Map& map);

	std::vector<Plant *> plants;
};

#endif //PLANTCONTAINER_HPP
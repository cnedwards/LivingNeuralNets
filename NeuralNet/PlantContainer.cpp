#include "PlantContainer.hpp"
const int PlantContainer::resurrectionTimer=900; //5 seconds

void PlantContainer::initiate(int initialPopulation, Map &map, TextureHolder &textures, b2World &world, int plantID)
{
	if (plantID==5) //Kelp
	{
	for (int loop=0; loop<initialPopulation; loop++)
		plants.push_back(new Kelp(rand() % map.getMapSize(),rand() % map.getMapSize(), map, textures, world));
	}
}

PlantContainer::~PlantContainer()
{
	empty();
}

void PlantContainer::update(b2World &world,sf::Time& elapsedTime, Map& map)
{
	int numberDead=0;
	for (int loop = 0; loop < plants.size(); loop++)
	{
		bool dead=plants[loop]->getDead();
		if (!dead)

		{
			plants[loop]->update(world, elapsedTime);
		}
		else plants[loop]->incrementTimeDead();
		numberDead+=dead; //messes up if I use ++

		int sideWidth=map.getSideWidth();
		if (plants[loop]->getTimeDead()>resurrectionTimer)
		{
			numberDead--; 
			plants[loop]->resurrect(world, map);
		}
	}

	if (numberDead>=plants.size())
		resurrect(world, map);
}


Plant* PlantContainer::getPlant(int index)
{
	return plants[index];
}

void PlantContainer::addPlant(Plant *newPlant)
{
	plants.push_back(newPlant);
}

int PlantContainer::amount()
{
	return plants.size();
}

int PlantContainer::amountAlive()
{
	int number=0;
	for (int loop=0; loop<plants.size(); loop++) {if (!(plants.at(loop)->getDead())) number++;}
	return number;
}

void PlantContainer::empty()
{
	for (int loop = 0; loop < plants.size(); loop++)
	{
        delete plants[loop];
	}
	plants.clear();
}

void PlantContainer::render(sf::RenderWindow &Window)
{
	for (int loop = 0; loop < plants.size(); loop++)
	{
		if (!plants[loop]->getDead())
		{
			plants[loop]->render(Window);
		}
	}
}

void PlantContainer::resurrect(b2World &world, Map& map)
{

	int sideWidth=map.getSideWidth();
	for (int loop = 0; loop < plants.size(); loop++)
	{
		plants[loop]->resurrect(world, map);
	}
}
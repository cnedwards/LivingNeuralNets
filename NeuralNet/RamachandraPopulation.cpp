#include "RamachandraPopulation.hpp"

void RamachandraPopulation::initiate(int initialPopulation, Map &map, TextureHolder &textures, b2World &world)
{
	for (int loop=0; loop<initialPopulation; loop++)
		monsters.push_back(new Ramachandra(rand() % map.getMapSize(),rand() % map.getMapSize(),map, textures, world));
}
#ifndef RAMACHANDRAPOPULATION_HPP
#define RAMACHANDRAPOPULATION_HPP

#include "NeuralNetwork/Population.hpp"
#include "Ramachandra.hpp"

class RamachandraPopulation : public Population
{
public:
    void initiate(int initialPopulation, Map &map, TextureHolder &textures, b2World &world);
};

#endif //RAMACHANDRAPOPULATION_HPP
#ifndef SIMLULATION_HPP
#define SIMLULATION_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D\Box2D.h>
#include "Map.hpp"
#include "EntityContainer.hpp"
#include <iostream>
#include <vector>
#include "TextureHolder.hpp"
#include "Ramachandra.hpp"
#include "RamachandraPopulation.hpp"
#include "PlantContainer.hpp"

class Simulation : private sf::NonCopyable
{
public:
	Simulation(int argMapSize, sf::RenderWindow &window, TextureHolder &textureHolder);
	~Simulation();
	void run();

private:
    ///basic
	void update(sf::Time elapsedTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void processEvents();

	int updates;

	RamachandraPopulation ramachandraPopulation;
	PlantContainer plantContainer;
	

	bool endGame;

	bool pause;
	int fastForward; bool reenableFastForward;

    static const sf::Time frameTime;

	sf::RenderWindow *Window;

	//camera
	sf::View view;
	bool movingLeft, movingRight, movingUp, movingDown;
	int viewScope; //Value between -8 and 5 for controlling zoom

	sf::Font font;//Sansation

	//textures
	TextureHolder *textures;

	//Stats
	sf::Text stats;
	sf::Time frameCountTime;
	int framesThisSecond;
	std::string displayFrames;
	void displayStats(sf::Time &elapsedTime);

	//World
		//Box2D
		b2World *world;
	Map map;
	int mapSize;//Pixels
};

#endif // SIMLULATION_HPP

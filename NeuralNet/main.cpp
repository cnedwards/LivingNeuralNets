#include "Simulation.hpp"
#include "MainMenu.hpp"
#include "TextureHolder.hpp"

int main()
{

	//Create main window
	sf::RenderWindow window(sf::VideoMode(700,800),  "Neural Net");
	
	//Load textures one time
	TextureHolder textures;

    srand((unsigned)time(0));

	//Create start menu
	MainMenu menu(window, textures);
	return 0;
}
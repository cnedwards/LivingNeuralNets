#ifndef MAINMENU_HPP
#define MAINMENU_HPP
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "AdjustMiddleButton.hpp"
#include "TextureHolder.hpp"

class MainMenu: public State
{

/// NOTE: inherited
public:
	MainMenu(sf::RenderWindow &Window, TextureHolder &texturesHolder);
private:
	static const sf::Time frameTime;
	virtual void render(sf::RenderWindow &Window);
	virtual void processEvents(sf::RenderWindow &Window);
	void run(sf::RenderWindow &Window);

	bool exitMenu;

	sf::Sprite sMainMenu;

	AdjustMiddleButton sPlayButton;

	//textures
	TextureHolder *textures;
};

#endif // MAINMENU_HPP

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.hpp"

class Button : public sf::Sprite
{

public:
	bool update(sf::RenderWindow &window);
	Button(const sf::Texture &texture);
	Button();

	///render is used instead of draw to allow seemless moving for buttons that need it
	void render(sf::RenderWindow &Window);

protected:
	sf::Clock cooldownCounter;
	const sf::Time cooldown;
};

#endif // BUTTON_HPP

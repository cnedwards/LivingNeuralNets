#ifndef ADJUSTMIDDLEBUTTON_HPP
#define ADJUSTMIDDLEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.hpp"
#include "Button.hpp"

///This class adjusts the position of the button from the middle when the screen size changes
class AdjustMiddleButton : public Button
{

public:
	bool update(sf::RenderWindow &Window);

	//constructors
	AdjustMiddleButton(const sf::Texture &texture);
	AdjustMiddleButton();
	///Position is from center.
	AdjustMiddleButton(const sf::Texture &texture, sf::Vector2f position);
	///Position is from center.
	AdjustMiddleButton(sf::Vector2f position);

	///Position must be according to the center of the screen
	///
	///It is not setPosition() because that interferes with access to Transformable.
	void position(sf::Vector2f position);
	void position(float x, float y);
	sf::Vector2f positionFromCenter;

	///render is used instead of draw to allow seemless moving for buttons that need it
	void render(sf::RenderWindow &Window);
};

#endif // ADJUSTMIDDLEBUTTON_HPP

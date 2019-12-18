#include "Button.hpp"

Button::Button(const sf::Texture &texture)
	:Sprite(texture),
	cooldown(sf::seconds(.2))
{}

Button::Button()
	:Sprite(),
	cooldown(sf::seconds(.2))
{}

bool Button::update(sf::RenderWindow &Window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldownCounter.getElapsedTime()>cooldown)
	{
		cooldownCounter.restart();
		sf::Vector2f relativeMousePosition=(sf::Vector2f)sf::Mouse::getPosition(Window);
		sf::Vector2f mouseClick=sf::Vector2f((Window.getView().getCenter().x-(Window.getSize().x/2))+relativeMousePosition.x,Window.getView().getCenter().y-(Window.getSize().y/2)+relativeMousePosition.y);
		if (getGlobalBounds().contains(mouseClick))
			return true;
	}

	return false;
}

void Button::render(sf::RenderWindow &Window)
{
	Window.draw(*this);
}
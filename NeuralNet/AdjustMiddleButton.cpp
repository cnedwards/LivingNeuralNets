#include "AdjustMiddleButton.hpp"

AdjustMiddleButton::AdjustMiddleButton(const sf::Texture &texture)
	:Button(texture)
{}

AdjustMiddleButton::AdjustMiddleButton()
	:Button()
{}

AdjustMiddleButton::AdjustMiddleButton(const sf::Texture &texture, sf::Vector2f position)
	:Button(texture),
	positionFromCenter(position)
{}

AdjustMiddleButton::AdjustMiddleButton(sf::Vector2f position)
	:Button(),
	positionFromCenter(position)
{}

bool AdjustMiddleButton::update(sf::RenderWindow &Window)
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

void AdjustMiddleButton::position(sf::Vector2f position)
{
    positionFromCenter=position;
}

void AdjustMiddleButton::position(float x, float y)
{
    positionFromCenter.x=x;
	positionFromCenter.y=y;
}

void AdjustMiddleButton::render(sf::RenderWindow &Window)
{
	//putting this here makes it seemless. It updates position every render not every timestep
	setPosition(Window.getView().getCenter().x + positionFromCenter.x, Window.getView().getCenter().y + positionFromCenter.y);

	Window.draw(*this);
}
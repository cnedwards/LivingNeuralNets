#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{

public:

Animation(sf::Time initSpriteTime/*=sf::Time(sf::seconds(.2))*/);

sf::IntRect getAnimation();

void addRectangle(sf::IntRect newRect);

bool newSprite();

private:
	sf::Clock clock;
	sf::Time spriteTime;

	std::vector<sf::IntRect> rectangles;

	int currentFrame;
};

#endif // ANIMATION_HPP
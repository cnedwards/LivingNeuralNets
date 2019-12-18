#ifndef STATE_HPP
#define STATE_HPP
#include <SFML/Graphics.hpp>

class State
{
public:
	State(sf::RenderWindow &Window, int frames);
private:
	static const sf::Time frameTime;
	virtual void render(sf::RenderWindow &Window);
	virtual void processEvents(sf::RenderWindow &Window);
	virtual void run(sf::RenderWindow &Window, int frames);

	sf::Texture splash;
	sf::Sprite sSplash;
};

#endif // STATE_HPP

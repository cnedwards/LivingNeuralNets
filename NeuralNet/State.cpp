#include "State.hpp"

const sf::Time State::frameTime = sf::seconds(1.f/180.f);

State::State(sf::RenderWindow &Window, int frames)
{
	/*run(Window, frames);*/
}

void State::run(sf::RenderWindow &Window, int frames)
{
	//splash.loadFromFile("Resource/splash.png");
	//sSplash.setTexture(splash);
	//sf::Clock clock;
 //   sf::Time timePassed = sf::Time::Zero;
	//int framesPassed=0;
 //       while (Window.isOpen())
 //           {
 //               sf::Time elapsedTime = clock.restart();
 //               timePassed += elapsedTime;
 //                   while(timePassed > frameTime)
 //                       {
	//						timePassed -= frameTime;//don't erase timestep required

 //                           render(Window);
	//						processEvents(Window);

	//						framesPassed++;//update frames passed
 //                       }
 //                   sf::sleep(frameTime-timePassed); //rests cpu while waiting to update/render

	//				if (framesPassed>=frames)//break the state loop if enough frames have passed
	//							break;
 //           }
}

void State::render(sf::RenderWindow &Window)
{
	/*Window.clear();
	Window.draw(sSplash);
	Window.display();*/
}

void State::processEvents(sf::RenderWindow &Window)
{
	/*sf::Event event;
	while (Window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				exit(0);
				break;
		}
	}*/
}
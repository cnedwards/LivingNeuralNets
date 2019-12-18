#include "MainMenu.hpp"
#include "Simulation.hpp"

const sf::Time MainMenu::frameTime = sf::seconds(1.f/180.f);

MainMenu::MainMenu(sf::RenderWindow &Window, TextureHolder &texturesHolder)
:State(Window, 0),
exitMenu(0),
textures(&texturesHolder),
sMainMenu(texturesHolder.tMainMenu),
sPlayButton(texturesHolder.tPlayButton, sf::Vector2f(-150/*x/2*/, 125/*y/2*/))
{
	sMainMenu.setTexture(texturesHolder.tMainMenu);
	sPlayButton.setTexture(texturesHolder.tPlayButton);
	run(Window);
}

void MainMenu::run(sf::RenderWindow &Window)
{
	sMainMenu.setPosition(Window.getView().getCenter().x-(Window.getSize().x/2),Window.getView().getCenter().y-(Window.getSize().y/2));
	
	sf::Clock clock;
    sf::Time timePassed = sf::Time::Zero;
	int framesPassed=0;

        while (Window.isOpen())
            {
				sMainMenu.setPosition(Window.getView().getCenter().x-(Window.getSize().x/2),Window.getView().getCenter().y-(Window.getSize().y/2));
				//sPlayButton.setPosition(Window.getView().getCenter().x-(Window.getSize().x/2)+225.f,Window.getView().getCenter().y-(Window.getSize().y/2)+400.f);

                sf::Time elapsedTime = clock.restart();
                timePassed += elapsedTime;
                    while(timePassed > frameTime)
                        {
							timePassed -= frameTime;//don't erase timestep required

                            render(Window);
							processEvents(Window);
							
							framesPassed++;//update frames passed
                        }
                    sf::sleep(frameTime-timePassed); //rests cpu while waiting to update/render

					if (exitMenu)//break the state loop if play button is pressed
						break;

					if (sPlayButton.update(Window))
					{
						Simulation simulation(2200, Window, *textures);
					}
            }
}

void MainMenu::render(sf::RenderWindow &Window)
{
	Window.clear();
	Window.draw(sMainMenu);
	sPlayButton.render(Window);
	Window.display();
}

void MainMenu::processEvents(sf::RenderWindow &Window)
{
	sf::Event event;
	while (Window.pollEvent(event))
	{
		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			Window.setView(sf::View(visibleArea));
		}

		switch(event.type)
		{
			case sf::Event::Closed:
				exit(0);
				break;
		}
	}
}
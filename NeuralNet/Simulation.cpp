#include "Simulation.hpp"
#include <Box2D\Box2D.h>

//Updates per second
const sf::Time Simulation::frameTime = sf::seconds(1.f/180.f);

//Box2D
const float timeStep=1.f/180.f;
const int32 velocityIterations = 6; 
const int32 positionIterations = 2; 
const int scale=30;//Box2D has 30 ppm (pixels per meter)

Simulation::Simulation(int argMapSize, sf::RenderWindow &window, TextureHolder &textureHolder)
    :Window(&window),
	textures(&textureHolder),
    pause(0), fastForward(1), reenableFastForward(0),
	world(new b2World(b2Vec2(0, 0))),
	map(argMapSize),
	view(Window->getDefaultView()),
	framesThisSecond(0),
	displayFrames("0"),
	endGame(0),
	movingLeft(0), movingRight(0), movingUp(0), movingDown(0),
	mapSize(argMapSize),
	viewScope(0)
	{
		Window->setView(view);

		font.loadFromFile("Resource/Sansation.ttf");
		stats.setFont(font); stats.setCharacterSize(15);
		         
		srand((unsigned)time(0));

		ramachandraPopulation.initiate(1, map, *textures, *world);
		plantContainer.initiate(15, map, *textures, *world, 5);

		//create map objects. Doing this in map constructor messes up world
		map.createMapBodies(*world);

        run();
	}

Simulation::~Simulation()
{
	//textures and window are declared on stack in main
	delete world;
	ramachandraPopulation.empty();//Frees entity memory
	plantContainer.empty();
}


void print(Population &p)
{
		long long g=p.getGenerationNumber();
		std::ofstream out("Networks/"+std::to_string(g)+".dat"); 
		p.print(out);
		out.close();
}

    void Simulation::run()
    {
		//Input
		std::ifstream in("GoodNetworks/good_abs_2.txt");
		ramachandraPopulation.read(in);
		in.close();
		
		/*//Optional output for testing
		std::ofstream out("test3.dat"); 
		ramachandraPopulation.print(out);
		out.close();
		exit(2);*/

		//Clear Networks directory
		std::string command = "del /Q ";
		std::string path = "Networks\\*.dat";
		system(command.append(path).c_str());


		updates=0; int generationNumber=ramachandraPopulation.getGenerationNumber();
        sf::Clock clock;
        sf::Time timePassed = sf::Time::Zero;
        while (Window->isOpen())
            {
				if (fastForward==1)
				{
                sf::Time elapsedTime = clock.restart();
                timePassed += elapsedTime;
                    while(timePassed > frameTime)
                        {
                            timePassed -= frameTime;

                            processEvents();
                            if (!pause)
                            {
								if (generationNumber<ramachandraPopulation.getGenerationNumber()) {updates=0; generationNumber=ramachandraPopulation.getGenerationNumber(); 
								print(ramachandraPopulation);}
								updates++; if (updates>16200) {updates=0; 
								print(ramachandraPopulation); ramachandraPopulation.newGeneration(*world, map); generationNumber++;}
								if (reenableFastForward) {fastForward=3; reenableFastForward=0;} //This ensures no lag when stopping fast forward

                                update(frameTime);
								world->Step(timeStep, velocityIterations, positionIterations);
                            }

					}


					render();
					displayStats(elapsedTime);

					if (endGame) break;
				}
				if (fastForward==2)
				{
					processEvents();
                            if (!pause)
                            {
								if (generationNumber<ramachandraPopulation.getGenerationNumber()) {updates=0; generationNumber=ramachandraPopulation.getGenerationNumber();
								print(ramachandraPopulation);}
								updates++; if (updates>16200) {updates=0; 
								print(ramachandraPopulation); ramachandraPopulation.newGeneration(*world, map); generationNumber++;}
								if (generationNumber%1000==0) {fastForward=1; reenableFastForward=1;} //This ensures no lag when stopping fast forward

                                update(frameTime);
								world->Step(timeStep, velocityIterations, positionIterations);
                            }

					render();
					displayStats(sf::Time(sf::Time::Zero));


					if (endGame) break;
				}

				else if (fastForward==3)
				{
					processEvents();
                            if (!pause)
                            {
								if (generationNumber<ramachandraPopulation.getGenerationNumber()) {updates=0; generationNumber=ramachandraPopulation.getGenerationNumber();
								print(ramachandraPopulation);}
								updates++; if (updates>16200) {updates=0; 
								print(ramachandraPopulation); ramachandraPopulation.newGeneration(*world, map); generationNumber++;}
								if (generationNumber%1000==0) {fastForward=1; reenableFastForward=1;} //This ensures no lag when stopping fast forward

                                update(frameTime);
								world->Step(timeStep, velocityIterations, positionIterations);
                            }


					if (endGame) break;
				}
            }
    }

	void Simulation::displayStats(sf::Time &elapsedTime)
	{
		//Fix positions to top left
		//Does not currently work with the zoom feature
		stats.setPosition(Window->getView().getCenter().x-(Window->getSize().x/2),Window->getView().getCenter().y-(Window->getSize().y/2));

		frameCountTime += elapsedTime;
					framesThisSecond++;

					if (frameCountTime >= sf::seconds(1.0f))
					{
						displayFrames=std::to_string((long double)framesThisSecond);

					frameCountTime -= sf::seconds(1.0f);
					framesThisSecond = 0;
					}
					stats.setString("Frames / Second = " + displayFrames + "\n"+
						"Generations = " + std::to_string((long long)ramachandraPopulation.getGenerationNumber()) + "\n"+
						"Updates = " + std::to_string((long long)updates) + "\n"+
						"Alive = " + std::to_string((long long)ramachandraPopulation.amountAlive()) + "\n"+
						"Number of entities: " +std::to_string((long long)ramachandraPopulation.amount()+plantContainer.amount()));
	}

    void Simulation::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
    {
			if (key==sf::Keyboard::W)
				movingUp=isPressed;
			if (key==sf::Keyboard::S)
				movingDown=isPressed;
			if (key==sf::Keyboard::A)
				movingLeft=isPressed;
			if (key==sf::Keyboard::D)
				movingRight=isPressed;

			
		if (key==sf::Keyboard::Q)
			ramachandraPopulation.empty();

		if (key == sf::Keyboard::P)
			pause=true;
		if (key == sf::Keyboard::O)
			pause=false;

		/*if (key == sf::Keyboard::Add)
			fastForward=true;
		if (key == sf::Keyboard::Subtract)
			fastForward=false;*/
		if (key == sf::Keyboard::Num1)	fastForward=1;
		if (key == sf::Keyboard::Num2)	fastForward=2;
		if (key == sf::Keyboard::Num3)	fastForward=3;

		if (key == sf::Keyboard::M)
			endGame=true;
    }

    void Simulation::processEvents()
{
	sf::Event event;
	while (Window->pollEvent(event))
	{
		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(Window->getView().getCenter().x-Window->getSize().x/2, Window->getView().getCenter().y-Window->getSize().y/2, event.size.width, event.size.height);
			view=sf::View(visibleArea);
			viewScope=0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			sf::FloatRect visibleArea(Window->getView().getCenter().x-Window->getSize().x/2, Window->getView().getCenter().y-Window->getSize().y/2, Window->getSize().x, Window->getSize().y);
			view=sf::View(visibleArea);
			view.setCenter(0,0);
			viewScope=0;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f relativeMousePosition=(sf::Vector2f)sf::Mouse::getPosition(*Window);
			sf::Vector2f mouseClick=sf::Vector2f((Window->getView().getCenter().x-(Window->getSize().x/2))+relativeMousePosition.x,Window->getView().getCenter().y-(Window->getSize().y/2)+relativeMousePosition.y);
			//ramachandraPopulation.addMonster(new Ramachandra(mouseClick.x,flipY(mouseClick.y),map, *textures, *world));
		}

		if (event.type== sf::Event::MouseWheelMoved)
		{
				if (event.mouseWheel.delta>0)
				{
					if (viewScope<5)
					{
						view.zoom(.9);
						viewScope++;
					}
				}

				if (event.mouseWheel.delta<0)
				{
					if (viewScope>-8)
					{
						view.zoom(1.111111111111111);
						viewScope--;
					}
				}
			}

		/*if (event.type == sf::Event::LostFocus)
			pause = 1;
		if (event.type == sf::Event::GainedFocus)
			pause = 0;*/

		switch(event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				exit(0);
				break;
		}
	}
}

void Simulation::update(sf::Time elapsedTime)
{
	ramachandraPopulation.update(*world, elapsedTime, map);
	plantContainer.update(*world, elapsedTime, map);

		if (movingLeft)
			view.move(-10,0);
        if (movingRight)
            view.move(10,0);
		if (movingUp)
			view.move(0,-10);
		if (movingDown)
			view.move(0,10);
}

	 void Simulation::render()
	 {
	    Window->clear();

		map.render(*Window);
		ramachandraPopulation.render(*Window);
		plantContainer.render(*Window);

		//stats
		Window->draw(stats);

		Window->setView(view);
        Window->display();
    }
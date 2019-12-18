#include "Sight.hpp"

	bool Sight::ReportFixture(b2Fixture* fixture) 
	{
		//std::cout<<"here";
		/*Entity* ball = static_cast<Entity*>( fixture->GetBody()->GetUserData() );
			if ( ball != NULL ) std::cout<<ball->getID()<<" "<<typeid(ball).name()<<std::endl;
			else std::cout<<typeid(fixture->GetBody()->GetUserData()).name()<<std::endl;
			std::cout<<std::endl<<std::endl;*/

		foundBodies.push_back( fixture->GetBody() );
		//std::cout<<foundBodies.size()<<" ";
		return true;//keep going to find all fixtures in the query area
		 std::cout<<std::endl<<std::endl;
	}

	//sight
	std::vector<b2Body*> Sight::getBodies(Sight &sight, b2World &world, dynamicBody &body, int boxSize, int size, int margin)
	{
		b2AABB aabb=getAABB(body,boxSize,size, margin);
		//sf::RectangleShape test; test.setSize(sf::Vector2f(25,25)); test.setPosition(sf::Vector2f(getCenterOnLine(body, size, boxSize).x, flipY(getCenterOnLine(body, size, boxSize).y))); window.draw(test);
		//aabb.upperBound.x=-300/30; aabb.upperBound.y=300/30; aabb.lowerBound.x=300/30; aabb.lowerBound.y=-300/30;


		world.QueryAABB( &sight, fixAABB(aabb)); //fix aabb to work
		//std::cout<<aabb.upperBound.x<<" "<<aabb.upperBound.y<<" "<<aabb.lowerBound.x<<" "<<aabb.lowerBound.y<<" "<<sight.foundBodies.size()<<std::endl;  
			/*Entity* ball = static_cast<Entity*>( sight.foundBodies[0]->GetUserData() );
			if ( ball != NULL ) std::cout<<ball->getID()<<" "<<typeid(ball).name()<<std::endl;
			else std::cout<<typeid(sight.foundBodies[0]->GetUserData()).name()<<std::endl;
			std::cout<<std::endl<<std::endl;*/
		return sight.foundBodies;
	}
	std::vector<b2Body*> Sight::getBodiesWorld(Sight &sight, b2World &world, dynamicBody &body, Map& map)
	{
		b2AABB aabb;
		aabb.lowerBound.x=0;
		aabb.lowerBound.y=0;
		aabb.upperBound.x=map.getMapSize()/30.f;
		aabb.upperBound.y=map.getMapSize()/30.f;
		//sf::RectangleShape test; test.setSize(sf::Vector2f(25,25)); test.setPosition(sf::Vector2f(getCenterOnLine(body, size, boxSize).x, flipY(getCenterOnLine(body, size, boxSize).y))); window.draw(test);
		//aabb.upperBound.x=-300/30; aabb.upperBound.y=300/30; aabb.lowerBound.x=300/30; aabb.lowerBound.y=-300/30;


		world.QueryAABB( &sight, fixAABB(aabb)); //fix aabb to work
		//std::cout<<aabb.upperBound.x<<" "<<aabb.upperBound.y<<" "<<aabb.lowerBound.x<<" "<<aabb.lowerBound.y<<" "<<sight.foundBodies.size()<<std::endl;  
			/*Entity* ball = static_cast<Entity*>( sight.foundBodies[0]->GetUserData() );
			if ( ball != NULL ) std::cout<<ball->getID()<<" "<<typeid(ball).name()<<std::endl;
			else std::cout<<typeid(sight.foundBodies[0]->GetUserData()).name()<<std::endl;
			std::cout<<std::endl<<std::endl;*/
		return sight.foundBodies;
	}

	b2AABB Sight::getAABB(dynamicBody &body, int boxSize, int size, int margin)
	{
		b2AABB aabb; 
		double r=size+boxSize;//Margin is not included in this r. Margin only matters for the distance between the body and its vision
		aabb.upperBound = getCenterOnLine(body, size, boxSize, margin);
		aabb.upperBound.x-=r/2.f; aabb.upperBound.y+=r/2.f;
		aabb.lowerBound = getCenterOnLine(body, size, boxSize, margin);
		aabb.lowerBound.x+=r/2.f; aabb.lowerBound.y-=r/2.f;
		//To Meters
		aabb.upperBound.x/=30.f; aabb.upperBound.y/=30.f;
		aabb.lowerBound.x/=30.f; aabb.lowerBound.y/=30.f;
		return aabb/*Box2d meters*/;
	}

	///Box2d QueryWorld only works correctly if the AABB is upperBound at top right and lowerBound at bottom left. 
	///Makes the x and y values 0 if they are negative(in first quadrant) and switches the upperBound x/y and lowerBound x/y if they so that upperBound is greater.
	b2AABB Sight::fixAABB(b2AABB aabb)
	{
		//Make no negatives because we are in first quadrant
		if (aabb.lowerBound.x<0) aabb.lowerBound.x=0;
		if (aabb.lowerBound.y<0) aabb.lowerBound.x=0;
		if (aabb.upperBound.x<0) aabb.upperBound.x=0;
		if (aabb.upperBound.y<0) aabb.upperBound.y=0;

		//Make sure upperBound values are greater
		if (aabb.upperBound.x<aabb.lowerBound.x) {float32 x= aabb.upperBound.x; aabb.upperBound.x=aabb.lowerBound.x; aabb.lowerBound.x=x;}
		if (aabb.upperBound.y<aabb.lowerBound.y) {float32 y= aabb.upperBound.y; aabb.upperBound.y=aabb.lowerBound.y; aabb.lowerBound.y=y;}


		return aabb;
	}

	void Sight::drawBox(b2AABB aabb/*Box2d meters*/, sf::RenderWindow &Window)
	{
		sf::Vertex line[] ={
		sf::Vertex(sf::Vector2f(aabb.upperBound.x*30, flipY(aabb.upperBound.y*30))),
		sf::Vertex(sf::Vector2f(aabb.lowerBound.x*30, flipY(aabb.lowerBound.y*30)))};

		line[0].color=sf::Color::Blue; line[1].color=sf::Color::Blue;

		Window.draw(line, 2, sf::Lines);

		line[0]=sf::Vector2f(aabb.upperBound.x*30, flipY(aabb.lowerBound.y*30));
		line[1]=sf::Vector2f(aabb.lowerBound.x*30, flipY(aabb.upperBound.y*30));
	
		Window.draw(line, 2, sf::Lines);
	}

	///Simply multiply the direction in coordinates by r (10+boxSize+size) that becomes the radius of a circle (based on entity rotation)
	b2Vec2 Sight::getCenterOnLine(dynamicBody &body, int size, int boxSize, int margin)
	{
		b2Vec2 direction;
		direction.x = (float) sin(body.body->GetAngle());
		direction.y = (float) cos(body.body->GetAngle());
		//Distance between center box and entity should be 10+boxSize+size
		double r=size+margin+boxSize;
		direction.x*=r; direction.y*=r;

		//Return Adjusted To Global Coordinates
		return b2Vec2(direction.x+(body.body->GetPosition().x*30), direction.y+(body.body->GetPosition().y*30));
	}
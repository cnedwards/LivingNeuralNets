#include "Animation.hpp"

Animation::Animation(sf::Time initSpriteTime/*=sf::Time(sf::seconds(.2))*/)
	:currentFrame(0),
	spriteTime(initSpriteTime)
{//create stuff
	clock.restart();
}

sf::IntRect Animation::getAnimation()
{
	if (rectangles.size()==0)
		return sf::IntRect(0,0,0,0);
	if (clock.getElapsedTime().asSeconds()>spriteTime.asSeconds()) //update the next frame returned if its greater than .1
	{
		currentFrame++;
		if (currentFrame>=rectangles.size())
			currentFrame=0;
		clock.restart();
	}
	return rectangles[currentFrame];
}


void Animation::addRectangle(sf::IntRect newRect)
{
	rectangles.push_back(newRect);
}

bool Animation::newSprite()
{
	if (clock.getElapsedTime().asSeconds()>spriteTime.asSeconds()) //update the next frame returned if its greater than .1
	{
		return true;
	}
	else
		return false;
}

//for creating rectangles from a spritesheet

//if (clock.getElapsedTime().asSeconds()>spriteTime.asSeconds()) //update the next frame returned if its greater than .1
//	{
//		currentFrame++;
//		if (currentFrame>frames)
//			currentFrame=0;
//		clock.restart();
//	}
//	
//	int row=0;
//	int framesLeft=frames;//for finding the row
//	while (framesLeft>currentFrame)
//	{
//		row++;
//		framesLeft -= xSprites;
//	}
//	//you find the rows and then how many it is into that row then turn that into x and y
//	int x=row*spriteX;
//	int y=framesLeft*spriteY;
//	//return sf::Sprite(texture, sf::IntRect(x, y, spriteX, spriteY));
//	return sf::IntRect(x, y, spriteX, spriteY);
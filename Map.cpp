#include "Map.h"
#include <Windows.h>



Map::Map(sf::Vector2f pos, sf::Texture tex, sf::Vector2f rect, float platformCount, sf::Texture platformTexture, sf::Texture wallTexture, sf::Texture coinTexture, int coinXRowAmountFrames, int coinYRowAmountFrames)
{
	this->srcRectangle = sf::IntRect(0, 0, coinTexture.getSize().x / coinXRowAmountFrames, coinTexture.getSize().y / coinYRowAmountFrames);
	this->myPlatformTexture = platformTexture;
	this->myPos = pos;
	this->myTex = tex;
	this->myRect = rect;
	this->myPlatformCount = platformCount;
	this->myWallTexture = wallTexture;
	this->myCoinTexture = coinTexture;
	this->myWallY = -(int)myWallTexture.getSize().y * 2;
	this->mySizeDifference = myPlatformTexture.getSize().x / myWallTexture.getSize().x;
	this->myPlatforms.resize(platformCount);
	this->myWalls.resize(mySizeDifference*platformCount);
	this->myWallCount = mySizeDifference*platformCount;
	this->myCoins.resize(platformCount / 3);
	this->myCoinCount = platformCount / 3;
	this->myCoinXRowAmountFrames = coinXRowAmountFrames;
	this->myCoinYRowAmountFrames = coinYRowAmountFrames;
	this->myCoinX = myPlatformTexture.getSize().x;
	this->myCoinY = -(int)myPlatformTexture.getSize().y / 2;
	srand(time(NULL));
	for (int i = 0; i < this->myWallCount - 1; i++)
	{
		if (i < 1)
		{
			this->myWallY += myWallTexture.getSize().y*1;
		}
		else
		{
			this->myWallY = -(int)myWallTexture.getSize().y * 2;
		}
		myWallPos = sf::Vector2f(this->myWallX, this->myWallY);
		this->myWalls[i].setSize((sf::Vector2f)myWallTexture.getSize());
		this->myWalls[i].setTexture(&myWallTexture);
		this->myWalls[i].setPosition(myWallPos);
		this->myWallX += myWallTexture.getSize().x;
	}
	this->myWallX = myWalls[0].getPosition().x;
	for (int i = 0; i < this->myPlatformCount - 1; i++)
	{
		myPlatformPos = sf::Vector2f(this->myPlatformX, this->myPlatformY);
		this->myPlatforms[i].setSize((sf::Vector2f)myPlatformTexture.getSize());
		this->myPlatforms[i].setTexture(&myPlatformTexture);
		this->myPlatforms[i].setPosition(myPlatformPos);
		this->myPlatformX += myPlatformTexture.getSize().x;
	}
	myBackground.setTexture(&myTex);
	myBackground.setPosition(myPos);
	myBackground.setSize(myRect);

}


Map::~Map()
{
}

//retunerar bakgrunds texturen.
sf::RectangleShape Map::getMap()
{
	return this->myBackground;
}

//void Map::moveMap()
//{
//	this->platformX += 1;
//	this->wallX += 1;
//	this->myPos.x += 1;
//}

//Retunerar platform vektorn.
std::vector<sf::RectangleShape> Map::getMyPlatforms()
{
	return this->myPlatforms;
}

//Retunerar vägg vektorn.
std::vector<sf::RectangleShape> Map::getMyWalls()
{
	return this->myWalls;
}

std::vector<sf::Sprite> Map::getMyCoins()
{
	return this->myCoins;
}

void Map::update()
{
	animation();
}


void Map::animation()
{
	//if (myCoinY > myPlatformTexture.getSize().y / 2)
	//{
	//	coinYSpeed = 5;
	//}
	//else if(myCoinY > 0)
	//{
	//	coinYSpeed = -5;
	//}
	//myCoinY += coinYSpeed;
	for (int i = 0; i < this->myCoinCount - 1; i++)
	{
		myCoinPos = sf::Vector2f(this->myCoinX+myPlatformTexture.getSize().x*i, this->myCoinY+1);
		this->myCoins[i].setTextureRect(this->srcRectangle);
		this->myCoins[i].setTexture(this->myCoinTexture);
		this->myCoins[i].setPosition(myCoinPos);
	}
	//myCoinY += 0.00000000001;
	//if (myCoinY > 3)
	//{
	//	myCoinY = 0;
	//}
	srcRectangle.left += srcRectangle.width;
	if (this->srcRectangle.left >= this->srcRectangle.width*(myCoinXRowAmountFrames))
	{
		srcRectangle.left = 0;
		srcRectangle.top += srcRectangle.height;
	}
	if (this->srcRectangle.top >= this->srcRectangle.height*(myCoinYRowAmountFrames))
	{
		srcRectangle.top = 0;
	}
}

//Ger bakgrunden olika värden
//void Map::setBackground()
//{
//	myBackground.setTexture(&myTex);
//	myBackground.setPosition(myPos);
//	myBackground.setSize(myRect);
//}

//Ger platformarna värden, men olika positioner
//void Map::setPlatforms()
//{
//	//this->myPlatforms[0].setSize((sf::Vector2f)myPlatformTexture.getSize());
//	//this->myPlatforms[0].setTexture(&myPlatformTexture);
//	//this->myPlatforms[0].setPosition(-(int)myPlatformTexture.getSize().x,-(int)myPlatformTexture.getSize().y);
//	//this->myPlatforms[1].setSize((sf::Vector2f)myPlatformTexture.getSize());
//	//this->myPlatforms[1].setTexture(&myPlatformTexture);
//	//this->myPlatforms[1].setPosition(-(int)myPlatformTexture.getSize().x, 0);
//	//this->myPlatforms[2].setSize((sf::Vector2f)myPlatformTexture.getSize());
//	//this->myPlatforms[2].setTexture(&myPlatformTexture);
//	//this->myPlatforms[2].setPosition(-(int)myPlatformTexture.getSize().x, -(int)myPlatformTexture.getSize().y*2);
//	//this->myPlatforms[3].setSize((sf::Vector2f)myPlatformTexture.getSize());
//	//this->myPlatforms[3].setTexture(&myPlatformTexture);
//	//this->myPlatforms[3].setPosition(myPlatformTexture.getSize().x, -(int)myPlatformTexture.getSize().y);
//	for (int i = 0; i < this->myPlatformCount-1; i++)
//	{
//		//sf::Vector2f platformPos(this->randomX, this->randomY);
//		//platformPos.x = this->randomX; platformPos.y = this->randomY;
//		platformPos = sf::Vector2f(this->platformX, this->platformY);
//		this->myPlatforms[i].setSize((sf::Vector2f)myPlatformTexture.getSize());
//		this->myPlatforms[i].setTexture(&myPlatformTexture);
//		this->myPlatforms[i].setPosition(platformPos);
//		this->platformX += myPlatformTexture.getSize().x;
//		//randomX += rand() % 100 + 300;
//		//randomX += rand() % myPlatformTexture.getSize().x / 3 + myPlatformTexture.getSize().x / 2;
//		//randomY += rand() % 300 - 150;
//	}
//	this->platformX = myPlatforms[0].getPosition().x;
//	this->platformY = myPlatforms[0].getPosition().y;
//}
//
////Ger väggarna värden, men olika positioner
//void Map::setWalls()
//{
//	for (int i = 0; i < this->myWallCount - 1; i++)
//	{
//		if (i < 1)
//		{
//			this->wallY += myWallTexture.getSize().y*1;
//		}
//		else
//		{
//			this->wallY = -(int)myWallTexture.getSize().y * 2;
//		}
//		wallPos = sf::Vector2f(this->wallX, this->wallY);
//		this->myWalls[i].setSize((sf::Vector2f)myWallTexture.getSize());
//		this->myWalls[i].setTexture(&myWallTexture);
//		this->myWalls[i].setPosition(wallPos);
//		this->wallX += myWallTexture.getSize().x;
//	}
//	this->wallX = myWalls[0].getPosition().x;
//}
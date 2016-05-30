#include "Map.h"



Map::Map(sf::Vector2f pos, sf::Texture tex, sf::Vector2f rect, float platformCount, sf::Texture platformTexture, sf::Texture wallTexture, 
sf::Texture coinTexture, int coinXRowAmountFrames, int coinYRowAmountFrames, sf::Texture bombTexture, int bombXRowAmountFrames, int bombYRowAmountFrames)
{
	this->srcCoinRectangle = sf::IntRect(0, 0, coinTexture.getSize().x / coinXRowAmountFrames, coinTexture.getSize().y / coinYRowAmountFrames);
	this->srcBombRectangle = sf::IntRect(0, 0, bombTexture.getSize().x / bombXRowAmountFrames, bombTexture.getSize().y / bombYRowAmountFrames);
	this->myPlatformTexture = platformTexture;
	this->myPos = pos;
	this->myTex = tex;
	this->myRect = rect;
	this->myPlatformCount = platformCount;
	this->myWallTexture = wallTexture;
	this->myCoinTexture = coinTexture;
	this->myBombTexture = bombTexture;
	this->myWallY = -(int)myWallTexture.getSize().y * 2;
	this->mySizeDifference = myPlatformTexture.getSize().x / myWallTexture.getSize().x;
	this->myPlatforms.resize(platformCount);
	this->myWalls.resize(mySizeDifference*platformCount);
	this->myWallCount = mySizeDifference*platformCount;
	this->myCoins.resize(platformCount);
	this->myCoinCount = platformCount;
	this->myCoinXRowAmountFrames = coinXRowAmountFrames;
	this->myCoinYRowAmountFrames = coinYRowAmountFrames;
	this->myBombs.resize(platformCount);
	this->myBombCount = platformCount;
	this->myBombXRowAmountFrames = bombXRowAmountFrames;
	this->myBombYRowAmountFrames = bombYRowAmountFrames;
	this->myBombX = myPlatformTexture.getSize().x;
	this->myBombY = -(int)myPlatformTexture.getSize().y / 7;
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
//sf::RectangleShape Map::getMap()
//{
//	return this->myBackground;
//}

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

std::vector<sf::Sprite> Map::getMyBombs()
{
	return this->myBombs;
}

void Map::update()
{
	animation();
}

void Map::coinVectorResize(int amount)
{
	this->myCoins.resize(myCoinCount - 1);
	this->myCoinCount -= 1 ;
	this->myCoins.erase(myCoins.begin());
	this->eraseCoinAmount++;
}

void Map::bombVectorResize(int amount)
{
	this->myBombs.resize(myBombCount - 1);
	this->myBombCount -= 1;
	this->myBombs.erase(myBombs.begin());
	this->eraseBombAmount++;
}


void Map::animation()
{
	//Coin animation
	for (int i = 0; i < this->myCoinCount - 1; i++)
	{
		myCoinPos = sf::Vector2f(this->myCoinX+myPlatformTexture.getSize().x*i+myPlatformTexture.getSize().x*this->eraseCoinAmount, this->myCoinY);
		this->myCoins[i].setTextureRect(this->srcCoinRectangle);
		this->myCoins[i].setTexture(this->myCoinTexture);
		this->myCoins[i].setPosition(myCoinPos);
	}
	srcCoinRectangle.left += srcCoinRectangle.width;
	if (this->srcCoinRectangle.left >= this->srcCoinRectangle.width*(myCoinXRowAmountFrames))
	{
		srcCoinRectangle.left = 0;
		srcCoinRectangle.top += srcCoinRectangle.height;
	}
	if (this->srcCoinRectangle.top >= this->srcCoinRectangle.height*(myCoinYRowAmountFrames))
	{
		srcCoinRectangle.top = 0;
	}

	//Bomb animation
	for (int i = 0; i < this->myBombCount - 1; i++)
	{
		myBombPos = sf::Vector2f(this->myBombX + myPlatformTexture.getSize().x*i + myPlatformTexture.getSize().x*this->eraseBombAmount - srcBombRectangle.width, this->myBombY);
		this->myBombs[i].setTextureRect(this->srcBombRectangle);
		this->myBombs[i].setTexture(this->myBombTexture);
		this->myBombs[i].setPosition(myBombPos);
	}
	//if (bombCollision == true)
	//{
	//	bombAnimation++;
	//	if (bombAnimation == 1)
	//	{
	//		this->srcBombRectangle.left += srcBombRectangle.width;
	//	}
	//}
	if (this->srcBombRectangle.left >= this->srcBombRectangle.width*(myBombXRowAmountFrames))
	{
		this->srcBombRectangle.left = 0;
	}
}

//void Map::bombCollisionCheck(bool p_collision)
//{
//	this->bombCollision = p_collision;
//}

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
#include "Game.h"



Game::Game(int lives, sf::Text pointsText)
{
	this->myLives = lives;
	this->myInitialLives = lives;
	this->myPointsText = pointsText;
}


Game::~Game()
{
}

bool Game::pointsCollision(sf::Sprite characterSprite, sf::Sprite sprite)
{
	if (characterSprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		myPoints += 1;
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::bombsCollision(sf::Sprite characterSprite, sf::Sprite sprite)
{
	if (characterSprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		myLives -= 1;
		return true;
	}
	else
	{
		return false;
	}
}

sf::Text Game::getMyPoints()
{
	std::stringstream ss;
	std::stringstream ssCoins;
	ss << "Coins: " << this->myPoints;
	myPointsText.setString(ss.str().c_str());
	myPointsText.setPosition(this->myPointsText.getPosition());
	return this->myPointsText;
}

void Game::update(sf::Vector2f updatePos)
{
	setTextPos(updatePos);
}


void Game::setTextPos(sf::Vector2f pointsPos)
{
	myPointsText.setPosition(pointsPos);
}

bool Game::endGameLife()
{
	if (this->myLives < this->myInitialLives)
	{
		return true;
	}
	else
	{
		return false;
	}
}

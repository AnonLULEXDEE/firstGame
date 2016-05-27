#include "Game.h"



Game::Game(int lives, sf::Text pointsText)
{
	this->myLives = lives;
	this->myPointsText = pointsText;
}


Game::~Game()
{
}

void Game::pointsCollision(sf::Sprite characterSprite, sf::Sprite sprite)
{
	if (characterSprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		myPoints += 1;
	}
}

sf::Text Game::getMyPoints()
{
	this->ss << this->myPoints;
	myPointsText.setString(this->ss.str().c_str());
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
#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
class Game
{
public:
	Game(int lives, sf::Text pointsText);
	~Game();
	bool Game::pointsCollision(sf::Sprite characterSprite, sf::Sprite sprite);
	sf::Text Game::getMyPoints();
	void Game::update(sf::Vector2f updatePos);
	void Game::setTextPos(sf::Vector2f pointsPos);
	bool Game::bombsCollision(sf::Sprite characterSprite, sf::Sprite sprite);
	bool Game::endGameLife();
private:
	sf::Font font;
	int myLives = 0;
	int myPoints = 0;
	int myInitialLives = 0;
	sf::Text myPointsText;
};


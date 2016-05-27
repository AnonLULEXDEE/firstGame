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
private:
	sf::Font font;
	int myLives = 0;
	int myPoints = 0;
	sf::Text myPointsText;
	std::stringstream ss;
};


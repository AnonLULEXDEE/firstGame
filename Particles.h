#pragma once
#include <SFML/Graphics.hpp>
class Particles
{
public:
	Particles(sf::Vector2f size, int amount, sf::Color color);
	~Particles();
	sf::CircleShape Particles::explosion();
private:
	sf::Vector2f mySize;
	int myAmount;
	sf::Color myColor;

};


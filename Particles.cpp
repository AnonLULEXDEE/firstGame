#include "Particles.h"


Particles::Particles(sf::Vector2f size, int amount, sf::Color color)
{
	this->myColor = color;
	this->myAmount = amount;
	this->mySize = size;
}


Particles::~Particles()
{
}

sf::CircleShape Particles::explosion()
{
	return sf::CircleShape();
}


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <windows.h>
#include <iostream>
#include <algorithm>  
#include "Character.h"
#include "Map.h"

int main()
{
	sf::ContextSettings settings;
	sf::Texture wallTexture;
	sf::Texture platformTexture;
	sf::Texture backgroundTexture;
	sf::Texture spriteSheet;
	sf::Texture coinSheet;
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(960, 540));
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Dat bois magical journey", sf::Style::Default, settings);
	window.setFramerateLimit(60);
	window.setView(view);
	if (!spriteSheet.loadFromFile("textures/spriteSheet3.png"))
		return EXIT_FAILURE;
	if (!backgroundTexture.loadFromFile("textures/background4.jpg"))
		return EXIT_FAILURE;
	if (!platformTexture.loadFromFile("textures/platformTexture3.jpg"))
		return EXIT_FAILURE;
	if (!wallTexture.loadFromFile("textures/wallTexture.jpg"))
		return EXIT_FAILURE;
	if (!coinSheet.loadFromFile("textures/coinSheet.png"))
		return EXIT_FAILURE;
		SFMLProject::Character Dude(6, 3, sf::Vector2f(wallTexture.getSize().x, -(float)spriteSheet.getSize().y/3), spriteSheet);
		Map levelOne(sf::Vector2f(0,-720), backgroundTexture, sf::Vector2f(1920, 1080), 40, platformTexture, wallTexture, coinSheet, 8, 8);
		std::vector<SFMLProject::Character> myAI{};
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.setView(view);
			levelOne.update();
			Dude.update();
			//window.draw(levelOne.getMap());
		/*	levelOne.moveMap();
			levelOne.moveMap();*/
			/*if (Dude.getMyPos == sf::Vector2f(0, 0))	
			{
				levelOne.moveMap();
			}*/
			window.draw(levelOne.getMap());
			for (auto n : levelOne.getMyPlatforms())
			{
				window.draw(n);
			}
			for (auto n : levelOne.getMyWalls())
			{
				window.draw(n);
			}
			for (auto n : levelOne.getMyCoins())
			{
				window.draw(n);
			}
			for (auto n : levelOne.getMyPlatforms())
			{
				Dude.CollisionY(n);
				if (Dude.getCollisionStatus() == SFMLProject::Character::collided || Dude.getCollisionStatus() == SFMLProject::Character::colliding)
				{
					std::cout << "Collided! ";
					break;
				}
			}
			for (auto n : levelOne.getMyWalls())
			{
				Dude.CollisionX(n);
				if (Dude.getXCollisionStatus() == SFMLProject::Character::collidingLeft)
				{
					std::cout << "CollidingLeft! ";
					break;
				}
				else if (Dude.getXCollisionStatus() == SFMLProject::Character::collidingRight)
				{
					std::cout << "CollidingRight! ";
					break;
				}
			}
			/*for (auto n : levelOne.getPlatforms())
			{
				Dude.Collision(n);
			}*/
			/*for (auto n : myAI)
			{
				Dude.Collision(n);
				if (Dude.getCollisionStatus() == true)
				{
					return EXIT_SUCCESS;
					break;
				}
			}*/
			/*Dude.Move(2, 0);*/
			if (Dude.endGame() == false)
			{
				MessageBox(0, "      YOU LOSE    ", "Warning", MB_OK | MB_ICONEXCLAMATION);
				return EXIT_SUCCESS;
			}
			window.draw(Dude.getMySprite());
			view.setCenter(Dude.getMyPos().x + Dude.getSize("x") / Dude.getSize("x") / 2 , -(int)platformTexture.getSize().y/3);
				//Dude.getMyPos().y + spriteTexture.getSize().y / Dude.getSize("x")/2);
			window.display();
		}
		return EXIT_SUCCESS;
}
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <limits.h>
#include <list>
	class Map
	{
	public:
		Map(sf::Vector2f pos, sf::Texture tex, sf::Vector2f rect, float platformCount, sf::Texture platformTexture, sf::Texture wallTexture, sf::Texture coinTexture, int coinXRowAmountFrames, int coinYRowAmountFrames);
		std::vector<sf::RectangleShape> Map::getMyPlatforms();
		std::vector<sf::RectangleShape> Map::getMyWalls();
		std::vector<sf::Sprite> Map::getMyCoins();
		sf::RectangleShape Map::getMap();	
	/*	void Map::setPlatforms();*/
		void Map::update();
		void Map::animation();
		/*void Map::setWalls();*/
		/*void Map::moveMap();*/
		/*void Map::setBackground();*/
		~Map();
	private:
		float mySizeDifference = 0;
		int myPlatformY = 0;
		int myPlatformX = 0;
		int myCoinY = 0;
		int myCoinX = 0;
		int myWallY = 0;
		int myWallX = 0;
		sf::IntRect srcRectangle;
		sf::Vector2f myPlatformPos;
		sf::Vector2f myWallPos;
		sf::Vector2f myCoinPos;
		sf::Texture myPlatformTexture;
		sf::Texture myWallTexture;
		sf::Texture myCoinTexture;
		sf::Vector2f myPos;
		sf::Sprite myCoinSprite;
		int mapWidth = 0;
		int mapHeight = 0;
		int myPlatformCount = 0;
		int myWallCount = 0;
		int myCoinCount = 0; 
		int myCoinXRowAmountFrames;
		int myCoinYRowAmountFrames;
		int coinYSpeed;
		sf::Texture myTex;
		sf::RectangleShape myBackground;
		sf::Vector2f myRect;
		std::vector<sf::RectangleShape> myPlatforms{};
		std::vector<sf::RectangleShape> myWalls{};
		std::vector<sf::Sprite> myCoins{};
	};

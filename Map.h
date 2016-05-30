#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <limits.h>
#include <list>
#include <Windows.h>   
	class Map
	{
	public:
		Map::Map(sf::Vector2f pos, sf::Texture tex, sf::Vector2f rect, float platformCount, sf::Texture platformTexture, sf::Texture wallTexture,
		sf::Texture coinTexture, int coinXRowAmountFrames, int coinYRowAmountFrames, sf::Texture bombTexture, int bombXRowAmountFrames, int bombYRowAmountFrames);

		std::vector<sf::RectangleShape> Map::getMyPlatforms();
		std::vector<sf::RectangleShape> Map::getMyWalls();
		std::vector<sf::Sprite> Map::getMyCoins();
		/*sf::RectangleShape Map::getMap();*/	
		void Map::coinVectorResize(int amount);
	/*	void Map::setPlatforms();*/
		void Map::update();
		void Map::animation();
		std::vector<sf::Sprite> Map::getMyBombs();
		void Map::bombVectorResize(int amount);
	/*	void Map::bombCollisionCheck(bool p_collision);*/
		/*void Map::setWalls();*/
		/*void Map::moveMap();*/
		/*void Map::setBackground();*/
		~Map();
	private:
		bool bombCollision;
		float mySizeDifference = 0;
		int bombAnimation = 0;
		int myPlatformY = 0;
		int myPlatformX = 0;
		int myCoinY = 0;
		int myCoinX = 0;
		int myBombY = 0;
		int myBombX = 0;
		int eraseBombAmount = 0;
		int eraseCoinAmount = 0;
		int myWallY = 0;
		int myWallX = 0;
		int mapWidth = 0;
		int mapHeight = 0;
		int myPlatformCount = 0;
		int myWallCount = 0;
		int myCoinCount = 0;
		int myCoinXRowAmountFrames;
		int myCoinYRowAmountFrames;
		int myBombCount = 0;
		int myBombXRowAmountFrames;
		int myBombYRowAmountFrames;
		int coinYSpeed;
		sf::IntRect srcCoinRectangle;
		sf::IntRect srcBombRectangle;
		sf::Vector2f myPlatformPos;
		sf::Vector2f myWallPos;
		sf::Vector2f myCoinPos;
		sf::Vector2f myBombPos;
		sf::Texture myPlatformTexture;
		sf::Texture myWallTexture;
		sf::Texture myCoinTexture;
		sf::Texture myBombTexture;
		sf::Vector2f myPos;
		sf::Sprite myCoinSprite;
		sf::Sprite myBombSprite;
		sf::Texture myTex;
		sf::RectangleShape myBackground;
		sf::Vector2f myRect;
		std::vector<sf::RectangleShape> myPlatforms{};
		std::vector<sf::RectangleShape> myWalls{};
		std::vector<sf::Sprite> myCoins{};
		std::vector<sf::Sprite> myBombs{};
	};

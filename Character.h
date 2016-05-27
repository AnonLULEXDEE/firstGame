#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <vector>
namespace SFMLProject
{
	class Character
	{
	public:
		Character(int xRowAmountFrames, int yRowAmountFrames, sf::Vector2f pos, sf::Texture tex);
		~Character();
		enum CollisionStatus
		{
			colliding,
			collided,
			notColliding,
			collidingRight,
			collidingLeft
		};
		void Character::update();
		sf::Sprite Character::getMySprite();
		sf::Vector2f Character::getMyPos();
		//void Character::setCollisionStatus(bool collisionStatus, sf::RectangleShape rect);
		void Character::setCollisionStatus(CollisionStatus myCurrentCollisionStatus);
		//void Character::Collision(sf::RectangleShape rect);
		//bool Character::getCollisionStatus();
		Character::CollisionStatus Character::getCollisionStatus();
		Character::CollisionStatus Character::getXCollisionStatus();
		void Character::CollisionX(sf::RectangleShape rect);
		bool Character::endGame();
		void Character::Move(int speedX, int speedY);
		void Character::CollisionY(sf::RectangleShape rect);
		int Character::getSize(std::string XY);
	private:
		float xFrameMovement = 0;
		float bottom, left, right, top;
		float mySpriteBottom, mySpriteLeft, mySpriteRight, mySpriteTop;
		float yFrameMovement = 0;
		int acceleration = 0;
		int spriteSwitch = 0;
		bool collisionStatus = false;
		int xRowAmountFrames;
		int yRowAmountFrames;
		sf::RectangleShape rect;
		sf::IntRect myGlobalBounds;
		sf::IntRect srcRectangle;
		sf::Image Image;
		sf::Vector2f myPos;
		sf::Texture myTex;
		sf::Sprite mySprite;
		sf::Vector2f oldPos;
		void Character::Movement();
		void Character::Physics();
		//void Character::Animation(); //Animerar i movement()
		CollisionStatus myCurrentCollisionStatus = notColliding;
		CollisionStatus myCurrentXCollisionStatus = notColliding;
		enum MovementState
		{
			rightwards,
			leftwards,
			upwards,
			downwards,
			neutral,
			none
		};
		MovementState myLastMovementState = none;
		MovementState myLastPhysicsState = none;

	protected:
	};
}


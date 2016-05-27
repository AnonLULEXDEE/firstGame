#include "Character.h"
using namespace SFMLProject;

Character::Character(int xRowAmountFrames, int yRowAmountFrames, sf::Vector2f pos, sf::Texture tex)
{
	this->xRowAmountFrames = xRowAmountFrames;
	this->yRowAmountFrames = yRowAmountFrames;
	this->myPos = pos;
	this->myTex = tex;
	this->srcRectangle = sf::IntRect(0, 0, tex.getSize().x / xRowAmountFrames, tex.getSize().y / yRowAmountFrames);
	mySprite.setTexture(this->myTex);
	mySprite.setPosition(this->myPos);
	mySprite.setTextureRect(this->srcRectangle);

}



Character::~Character()
{
}

//Sätter en collision status
void Character::setCollisionStatus(CollisionStatus myCurrentCollisionStatus)
{ 
	this->myCurrentCollisionStatus = myCurrentCollisionStatus;
	//if (this->myCurrentCollisionStatus == colliding && myLastPhysicsState == downwards)
	//{
	//	/*myPos.y = rect.getPosition().y - srcRectangle.height+0.001;*/
	//}
}

//Uppdaterar variabler osv.
void Character::update()
{
	Physics();
	Movement();
	endGame();
}

//Retunerar Character's sprite.
sf::Sprite Character::getMySprite()
{
	return this->mySprite;
}

//Retunerar Character's position 
sf::Vector2f Character::getMyPos()	
{
	return this->myPos;
}


//Flyttar på spriten och tar hand om sprite switchen samt kollar om spriten rör sig neråt, uppåt eller är neutral.
void Character::Movement()
{
	oldPos.y = myPos.y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->myCurrentCollisionStatus == collided)
	{
		yFrameMovement = -15;
		myLastPhysicsState = upwards;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (myLastMovementState == none || myLastMovementState == rightwards)
		{
			srcRectangle.top = srcRectangle.height;
			srcRectangle.left = 0;
			myLastMovementState = leftwards;
		}
		if (this->srcRectangle.left >= this->srcRectangle.width*(xRowAmountFrames - 1))
		{
			srcRectangle.left = 0;
		}
		if (this->spriteSwitch == 4 && this->myCurrentCollisionStatus == collided)
		{
			srcRectangle.left += srcRectangle.width;
			this->spriteSwitch = 0;
		}
		else if (spriteSwitch < 4)
		{
			this->spriteSwitch++;
		}
		if (myCurrentXCollisionStatus == collidingLeft)
		{
			myPos.x += 0;
		}
		else
		{
			myPos.x -= 7; // 7
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (myLastMovementState == none || myLastMovementState == leftwards)
		{
			srcRectangle.top = 0;
			srcRectangle.left = 0;
			myLastMovementState = rightwards;
		}
		if (this->srcRectangle.left >= this->srcRectangle.width*(xRowAmountFrames - 1))
		{
			srcRectangle.left = 0;
		}
		if(this->spriteSwitch == 4 && this->myCurrentCollisionStatus == collided)
		{
			srcRectangle.left += srcRectangle.width;
			this->spriteSwitch = 0;
		}
		else if (spriteSwitch < 4)
		{
			this->spriteSwitch++;
		}
		if (myCurrentXCollisionStatus == collidingRight)
		{
			myPos.x -= 0;
		}
		else
		{
			myPos.x += 30; // 7
		}


	}
	else {
		if (myLastMovementState == rightwards)
		{
			srcRectangle.left = 0;
		}
		else if(myLastMovementState == leftwards)
		{
			srcRectangle.left = srcRectangle.width;
		}
		srcRectangle.top = srcRectangle.height + srcRectangle.height;
		myLastMovementState = none;
		
	}
	myPos.y += yFrameMovement;
	mySprite.setPosition(this->myPos);
	mySprite.setTextureRect(this->srcRectangle);
	if (oldPos.y < myPos.y)
	{
		myLastPhysicsState = downwards; 
	}
	else if (oldPos.y > myPos.y)
	{
		myLastPhysicsState = upwards;
	}
	else
	{
		myLastPhysicsState = neutral;
	}
}

//void Character::Collision(sf::RectangleShape rect)
//{
//	if (mySprite.getGlobalBounds().intersects(rect.getGlobalBounds()) && myLastPhysicsState == downwards)
//	{
//		setCollisionStatus(true, rect);
//	}
//	else if (myLastPhysicsState == upwards || myLastPhysicsState == neutral)
//	{
//		setCollisionStatus(false, rect);
//	}   
//
//}

//Kollar collision i Y-ledd genom att kolla alla fyra hörn på objektet man kolliderar med samt spriten's enga fyra hörn.
void Character::CollisionY(sf::RectangleShape rect)
{
	this->mySpriteBottom = this->mySprite.getPosition().y + mySprite.getTextureRect().height;
	this->mySpriteLeft = this->mySprite.getPosition().x;
	this->mySpriteRight = this->mySprite.getPosition().x + mySprite.getTextureRect().width;
	this->mySpriteTop = this->mySprite.getPosition().y;
	bottom = rect.getPosition().y + rect.getTextureRect().height;
	left = rect.getPosition().x;
	right = rect.getPosition().x + rect.getTextureRect().width;
	top = rect.getPosition().y;
	//right > mySpriteLeft || left > mySpriteRight || 
	//right <= p.left || left >= p.right || top >= p.bottom || bottom <= p.top
	if (top > mySpriteBottom || bottom < mySpriteTop)
	{
		setCollisionStatus(notColliding);
	}
	else
	{
		setCollisionStatus(collided);
	}
	if (!mySprite.getGlobalBounds().intersects(rect.getGlobalBounds()))
	{
		setCollisionStatus(notColliding);
	}
}

//Kollar collision i X-ledd genom att kolla alla fyra hörn på objektet man kolliderar med samt spriten's enga fyra hörn.
void Character::CollisionX(sf::RectangleShape rect)
{
	if (mySprite.getGlobalBounds().intersects(rect.getGlobalBounds()))
	{
	this->mySpriteBottom = this->mySprite.getPosition().y + mySprite.getTextureRect().height;
	this->mySpriteLeft = this->mySprite.getPosition().x;
	this->mySpriteRight = this->mySprite.getPosition().x + mySprite.getTextureRect().width;
	this->mySpriteTop = this->mySprite.getPosition().y;
	bottom = rect.getPosition().y + rect.getTextureRect().height;
	left = rect.getPosition().x;
	right = rect.getPosition().x + rect.getTextureRect().width;
	top = rect.getPosition().y;
		if (true)
		{
			if (right >= mySpriteLeft)
			{
				this->myCurrentXCollisionStatus = collidingLeft;
			}
			else
			{
				this->myCurrentXCollisionStatus = notColliding;
			}
		}
		else
		{
			if (left <= mySpriteRight)			// if (top < mySpriteBottom && left < mySpriteRight)
			{
				this->myCurrentXCollisionStatus = collidingRight;
			}
			else if (myCurrentXCollisionStatus != collidingLeft)
			{
				this->myCurrentXCollisionStatus = notColliding;
			}
		}
	}
	else
	{
		this->myCurrentXCollisionStatus = notColliding;
	}
}

//Snabb funktion för konstant rörelse.
void Character::Move(int speedX, int speedY)
{
	myPos.x += speedX;
	myPos.y += speedY;
}

//retunerar y-ledd collision status
Character::CollisionStatus Character::getCollisionStatus()
{
	return this->myCurrentCollisionStatus;
}

//retunerar x-ledd collision status
Character::CollisionStatus Character::getXCollisionStatus()
{
	return this->myCurrentXCollisionStatus;
}

//Fysiken som ger spriten en konstant rörelse om den inte kolliderar.
void Character::Physics()
{
	if (this->myCurrentCollisionStatus == collided)
	{
		yFrameMovement = 0;
	}
	else if (this->myCurrentCollisionStatus == notColliding || myLastPhysicsState == upwards || myLastPhysicsState == neutral)
	{
		yFrameMovement += 1;
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->myPos.y -= 1;
	}*/  // Used for ducking

}

//Snabb funktion som retunerar storleken på spriten, både bredd och längd.
int Character::getSize(std::string XY)
{
	if (XY == "x")
	{
		return this->myTex.getSize().x;
	}
	else if (XY == "y")
	{
		return this->myTex.getSize().y;
	}
	else
	{
		return false;
	}
}

//Simpel funktion som retunerar false om man har fallit under en viss punkt i y.
bool Character::endGame()
{
	if (this->myPos.y > 2000)
	{
		return false;
	}
	else
	{
		return true;
	}
}

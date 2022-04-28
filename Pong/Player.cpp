#include "Player.h"

//constructor for player
Player::Player()
{
	initVariables();
	initShape();
}

Player::~Player()
{
	// no memory dynamically allocated; nothing happens here
}

//updates the window/moves the player
void Player::update(const sf::RenderTarget* target)
{
	// move the player

	updateInput(); // check for pressed keys
	updateWindowsBoundsCollision(target); // window bounds collision	
}

//controls how the player moves through the use of key events
void Player::updateInput()
{
	// keyboard input

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // A is pressed on the keyboard
	{
		sprite.move(-movementSpeed, 0.f); // move to the left
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // D is pressed on the keyboard
	{
		sprite.move(movementSpeed, 0.f); // move to the right
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // W is pressed on the keyboard
	{
		sprite.move(0.f, -movementSpeed); // move up
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // S is pressed on the keyboard
	{
		sprite.move(0.f, movementSpeed); // move down
	}
}

//checks if the player collides with the bounds of the window
void Player::updateWindowsBoundsCollision(const sf::RenderTarget* target)
{

	if (sprite.getGlobalBounds().left <= 0.f) // left
	{
		sprite.setPosition(0.f, sprite.getGlobalBounds().top);
	}
	else if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >= target->getSize().x) // right
	{
		sprite.setPosition(target->getSize().x - sprite.getGlobalBounds().width, sprite.getGlobalBounds().top);
	}

	if (sprite.getGlobalBounds().top <= 0.f) // top-> return to bottom!! win condition
	{
		sprite.setPosition((target->getSize().x - sprite.getGlobalBounds().width) / 2,
			target->getSize().y - sprite.getGlobalBounds().height - 20);
		// increment points
		points++;

	}
	else if (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height >= target->getSize().y) // bottom
	{
		sprite.setPosition(sprite.getGlobalBounds().left, target->getSize().y - sprite.getGlobalBounds().height);
	}

}

//Draws the sprite
void Player::render(sf::RenderTarget *target)
{
	target->draw(sprite);
}

//Sets the position of the sprite
void Player::setPos(float x, float y)
{
	sprite.setPosition(x, y);
}

//gets the players current points
int Player::getPoints()
{
	return points;
}

//gets the players current health
int Player::getHP()
{
	return hp;
}

//sets the players health
void Player::setHP(int newHP)
{
	hp = newHP;
}

//initializes variables for the constructor
void Player::initVariables()
{
	movementSpeed = 3.f; // movement speed slower than the circles so its more FUN
	hpMax = 3; // 3 lives then game over
	hp = hpMax;
	points = 0;
}

//initializes the sprite
void Player::initShape()
{
	texture.loadFromFile("Textures/AndyOfallon.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(9, 2, 13, 29));
	sprite.setScale(sf::Vector2f(2.0, 2.0));
	/*setFillColor(sf::Color::Green);
	setSize(sf::Vector2f(30.f, 30.f));*/
	//shape.setScale(0.5f, 0.5f); // reduces size by 50%
}

//returns a pointer to a sprite
sf::Sprite* Player::getSprite()
{
	return &sprite;
}

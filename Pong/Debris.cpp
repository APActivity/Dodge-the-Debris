#include "Debris.h"

//sets the debris in window
Debris::Debris(const sf::RenderTarget& window)
{
	initShape(window);
}

Debris::~Debris()
{

}

//sf::Sprite* Debris::getSprite()
//{
//	return &sprite; Implementation for making the debris into sprites in the future...
//}

//updates the windows position of the debris
void Debris::update(const sf::RenderTarget* target)
{
	if (getGlobalBounds().left <= 0.f) // left
	{
		speed *= -1;
	}
	else if (getGlobalBounds().left + getGlobalBounds().width >= target->getSize().x) // right
	{
		speed *= -1;
	}

	move(speed, 0.f);
}

//draws the actual debris
void Debris::render(sf::RenderTarget& target)
{
	target.draw(*this);
}

//initializes the radius, color, and position of all of the debris
void Debris::initShape(const sf::RenderTarget& window)
{
	setRadius(10.f);
	sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	setFillColor(color);
	int midX = (window.getSize().x - getGlobalBounds().width) / 2;
	int maxY = window.getSize().y - getGlobalBounds().height - 150;
	setPosition(sf::Vector2f(
		static_cast<float>(midX),
		static_cast<float>(rand() % maxY + getGlobalBounds().height)));
	speed = 5;
}

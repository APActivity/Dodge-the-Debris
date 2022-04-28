#pragma once

#include<iostream>
#include<ctime>

#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>


class Player //: public sf::RectangleShape
{
public:
	Player();
	virtual ~Player();

	void update(const sf::RenderTarget* target);
	void updateInput();
	void updateWindowsBoundsCollision(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
	void setPos(float x, float y);
	int getPoints();
	int getHP();
	void setHP(int newHP);
	sf::Sprite* getSprite();


private:
	float movementSpeed;
	int hp;
	int hpMax;
	int points;
	sf::Sprite sprite;
	sf::Texture texture;
	void initVariables();
	void initShape();
	friend class Test;
};


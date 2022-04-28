#pragma once

#include "Player.h" // where all the libraries are

class Debris : public sf::CircleShape
{
public:
	Debris(const sf::RenderTarget& window);
	virtual ~Debris();
	sf::Sprite* getSprite();
	void update(const sf::RenderTarget* target);
	void render (sf::RenderTarget& target);

private:
	float speed;

	void initShape(const sf::RenderTarget& window);
	/*sf::Sprite sprite;
	sf::Texture texture;*/
	friend class Test;
};


#pragma once
#include"Game.h"
#include<sstream>

class GameOver
{
public:
	GameOver();
	~GameOver();

	void initFont();
	void initText(int highScore);
	void render(sf::RenderWindow& window);
	void MoveSelectionUp();
	void MoveSelectionDown();
	void testGameOver();
	bool gameOverMenu(int highScore);
	void initWindow();




private:
	sf::Text gameOverText[4];
	sf::Font font;
	int selectedItemIndex;
	sf::RenderWindow* gameOverWindow;
};


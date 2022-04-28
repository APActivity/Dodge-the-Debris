#pragma once
#include"Game.h"
#include"GameOver.h"
#define MAX_ITEMS 2

class Menu // menu controls the game
{
public:
	Menu();
	~Menu();

	void render(sf::RenderWindow &window);
	void MoveSelectionUp();
	void MoveSelectionDown();
	int getSelection();
	void runGame();
	void initText();
	void initFont();
	void initWindow();

protected:

	int selectedItemIndex;
	sf::Font font;
	sf::Text text[MAX_ITEMS]; // size of 3 options
	sf::Text guiText;
	sf::RenderWindow* menuWindow;

	friend class Test;
};


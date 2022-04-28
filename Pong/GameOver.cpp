#include "GameOver.h"

/*
-These functions are all the same as Menu.cpp functions
Adapted using inheritance and polymorphism to overload the text in the window, number of options in the menu, etc.
*/
GameOver::GameOver()
{
	initWindow();
	initFont();
	selectedItemIndex = 2;
}

GameOver::~GameOver()
{
	delete gameOverWindow;
}

void GameOver::initWindow()
{
	gameOverWindow = new sf::RenderWindow(sf::VideoMode(800, 800), "Game Over Menu", sf::Style::Titlebar | sf::Style::Close);
}

void GameOver::initFont()
{
	if (!font.loadFromFile("Fonts/game_over.ttf"))
	{
		std::cout << "Font file not loaded" << std::endl;
	}
}

void GameOver::initText(int highScore)
{
	gameOverText[0].setFont(font);
	gameOverText[0].setColor(sf::Color::White);
	gameOverText[0].setString("Game Over");
	gameOverText[0].setPosition(sf::Vector2f((gameOverWindow->getSize().x) / 2 - 2 * gameOverText[0].getGlobalBounds().width,
		(gameOverWindow->getSize().y - gameOverText[0].getGlobalBounds().height) / 5 * 1));
	gameOverText[0].setCharacterSize(150.f);

	std::stringstream ss;
	ss << "High Score: " << highScore; // put the high score into a string to display

	gameOverText[1].setFont(font);
	gameOverText[1].setColor(sf::Color::White);
	gameOverText[1].setString(ss.str());
	gameOverText[1].setPosition(sf::Vector2f((gameOverWindow->getSize().x) / 2 - 2 * gameOverText[1].getGlobalBounds().width,
		(gameOverWindow->getSize().y - gameOverText[1].getGlobalBounds().height) / 5 * 2));
	gameOverText[1].setCharacterSize(150.f);

	gameOverText[2].setFont(font);
	gameOverText[2].setColor(sf::Color::Green);
	gameOverText[2].setString("Return to Menu");
	gameOverText[2].setPosition(sf::Vector2f((gameOverWindow->getSize().x) / 2 - 2 * gameOverText[2].getGlobalBounds().width,
		(gameOverWindow->getSize().y - gameOverText[2].getGlobalBounds().height) / 5 * 3));
	gameOverText[2].setCharacterSize(150.f);

	gameOverText[3].setFont(font);
	gameOverText[3].setColor(sf::Color::White);
	gameOverText[3].setString("Exit");
	gameOverText[3].setPosition(sf::Vector2f((gameOverWindow->getSize().x) / 2 - 2 * gameOverText[3].getGlobalBounds().width,
		(gameOverWindow->getSize().y - gameOverText[3].getGlobalBounds().height) / 5 * 4));
	gameOverText[3].setCharacterSize(150.f);
}

void GameOver::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		window.draw(gameOverText[i]);
	}
}

void GameOver::MoveSelectionUp()
{
	if (selectedItemIndex - 1 >= 2)
	{
		gameOverText[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		gameOverText[selectedItemIndex].setColor(sf::Color::Green);
	}
}

void GameOver::MoveSelectionDown()
{
	if (selectedItemIndex + 1 < 4)
	{
		gameOverText[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		gameOverText[selectedItemIndex].setColor(sf::Color::Green);
	}
}

void GameOver::testGameOver()
{
	initText(69);
	sf::Event event;

	while (gameOverWindow->isOpen())
	{
		while (gameOverWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				{
					this->MoveSelectionUp();
					break;
				}
				case sf::Keyboard::S:
				{
					this->MoveSelectionDown();
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (selectedItemIndex)
					{
					case 2: // play again
					{
						std::cout << "play again selected" << std::endl;
						gameOverWindow->close();
						break;
					}
					case 3:
					{
						gameOverWindow->close();
						break;
					}
					}
					break;
				case sf::Keyboard::Escape:
				{
					gameOverWindow->close();
					break;
				}
				}
				}
			}
			}
			gameOverWindow->clear();
			render(*gameOverWindow);
			gameOverWindow->display();
		}
	}
}

bool GameOver::gameOverMenu(int highScore)
{
	initText(highScore);
	sf::Event event;
	int returnValue = false; // returns true to Exit the game; false to return to the main menu

	while (gameOverWindow->isOpen())
	{
		while (gameOverWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				{
					this->MoveSelectionUp();
					break;
				}
				case sf::Keyboard::S:
				{
					this->MoveSelectionDown();
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (selectedItemIndex)
					{
					case 2: // return to menu
					{
						gameOverWindow->close();
						break;
					}
					case 3: // exit
					{
						gameOverWindow->close();
						returnValue = true; // exit the game
						break;
					}
					}
					break;
				case sf::Keyboard::Escape:
				{
					gameOverWindow->close();
					returnValue = true; // exit the game default key
					break;
				}
				}
				}
			}
			}
			gameOverWindow->clear();
			render(*gameOverWindow);
			gameOverWindow->display();
		}
	}
	return returnValue;
}

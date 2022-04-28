#include "Menu.h"

//initializes the window, font, index of selection, and text that will be generated
Menu::Menu()
{
	initWindow();
	initFont();
	initText();
	selectedItemIndex = 0;
}

Menu::~Menu()
{
	delete menuWindow;
}

//Draws to the window
void Menu::render(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(text[i]);
	}
}

//Moves the selection up in the menu
void Menu::MoveSelectionUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		text[selectedItemIndex].setColor(sf::Color::Green);
	}
}

//Moves the selection down in the menu
void Menu::MoveSelectionDown()
{
	if (selectedItemIndex + 1 < MAX_ITEMS)
	{
		text[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		text[selectedItemIndex].setColor(sf::Color::Green);
	}
}

//returns the index of selection 
int Menu::getSelection()
{
	return selectedItemIndex;
}

//intializes the window size
void Menu::initWindow()
{
	menuWindow = new sf::RenderWindow(sf::VideoMode(800, 800), "Main Menu", sf::Style::Titlebar | sf::Style::Close);
}

//loads the font
void Menu::initFont()
{
	if (!font.loadFromFile("Fonts/game_over.ttf"))
	{
		std::cout << "Font file not loaded" << std::endl;
	}
}

//Initializes the text that will be displayed on the menu
void Menu::initText()
{
	text[0].setFont(font);
	text[0].setColor(sf::Color::Green);
	text[0].setString("Play Game");
	text[0].setPosition(sf::Vector2f((menuWindow->getSize().x) / 2 - 2 * text[0].getGlobalBounds().width, 
		(menuWindow->getSize().y - text[0].getGlobalBounds().height) / (MAX_ITEMS + 1) * 1));

	text[0].setCharacterSize(150.f);

	text[1].setFont(font);
	text[1].setColor(sf::Color::White);
	text[1].setString("Exit Game");
	text[1].setPosition(sf::Vector2f((menuWindow->getSize().x) / 2 - 2 * text[1].getGlobalBounds().width,
		(menuWindow->getSize().y - text[1].getGlobalBounds().height) / (MAX_ITEMS + 1) * 2));
	text[1].setCharacterSize(150.f);
}

//Runs the menu (i.e move up and down/ select option)
void Menu::runGame()
{
	sf::Event event;
	bool exitGame = false; // return value from GameOver class

	while (menuWindow->isOpen())
	{
		while (menuWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				{
					MoveSelectionUp();
					break;
				}
				case sf::Keyboard::S:
				{
					MoveSelectionDown();
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (selectedItemIndex)
					{
					case 0: // play
					{
						Game game;
						while (game.isRunning())
						{
							if (game.isGameOver())
							{
								// game over window
								game.storeHighScore();
								GameOver go;
								exitGame = go.gameOverMenu(stoi(game.getHighScore())); // convert string to int for gameOver menu to process
								break;
							}
							else
							{
								// UPDATE
								game.update();

								// RENDER
								game.render();
							}

						}
						
						if (exitGame == true)
						{
							menuWindow->close();
						}
						break;
					}
					case 1:
					{
						menuWindow->close();
						break;
					}
					}
					break;
				}
				case sf::Keyboard::Escape:
				{
					menuWindow->close();
					break;
				}
				}
			}
			}
		}
		menuWindow->clear();
		render(*menuWindow);
		menuWindow->display();
	}
}

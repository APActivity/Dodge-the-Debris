#include "Test.h"

Test::Test()
{
}

Test::~Test()
{
}
//function that runs all the tests
void Test::runTests()
{
	if (!testRenderWindow())
	{
		std::cout << "Render Window test FAILURE" << std::endl;
	}
	else
	{
		std::cout << "Render Window test SUCCESS" << std::endl;
	}

	system("pause");

	if (!testPlayer())
	{
		std::cout << "Player test FAILURE" << std::endl;
	}
	else
	{
		std::cout << " Player test SUCCESS" << std::endl;
	}

	system("pause");

	if (!testDebris())
	{
		std::cout << "Debris test FAILURE" << std::endl;
	}
	else
	{
		std::cout << "Debris test SUCCESS" << std::endl;
	}

	system("pause");

	if (!testGameLoop())
	{
		std::cout << "Game Loop test FAILURE" << std::endl;
	}
	else
	{
		std::cout << "Game Loop test SUCCESS" << std::endl;
	}

	system("pause");

	if (!testMenu())
	{
		std::cout << "Menu test FAILURE" << std::endl;
	}
	else
	{
		std::cout << "Menu test SUCCESS" << std::endl;
	}

	system("pause");
}

// SUCCESS: renders an empty window
bool Test::testRenderWindow()
{
	bool success = false;

	float width = 800;
	float height = 800;

	sf::Event event;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width,height), "Window Test", sf::Style::Titlebar | sf::Style::Close);

	while (window->isOpen()) // HIT ESCAPE TO CLOSE THE WINDOW
	{
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: // close window
			{
				window->close(); // manually close the window
				break;
			}
			case sf::Event::KeyPressed: // key is pressed
			{
				if (event.key.code == sf::Keyboard::Escape) // close window if Escape is pressed too
				{
					window->close();
				}
				break;
			}
			}
		}
		window->clear();
		window->display();
	}

	if (window != nullptr)
	{
		success = true;
	}

	delete window; // deallocate memory

	return success;
}

// SUCCESS: loads the player sprite
bool Test::testPlayer()
{
	bool success = false;

	float width = 800;
	float height = 800;

	Player* player = new Player();

	if (player != nullptr)
	{
		success = true;
	}

	sf::Event event;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Player Test", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60); // so frame rate doesn't get too high

	while (window->isOpen()) // HIT ESCAPE TO CLOSE THE WINDOW
	{
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: // close window
			{
				window->close(); // manually close the window
				break;
			}
			case sf::Event::KeyPressed: // key is pressed
			{
				if (event.key.code == sf::Keyboard::Escape) // close window if Escape is pressed too
				{
					window->close();
				}
				break;
			}
			}
		}

		player->update(window);

		window->clear();
		player->render(window);
		window->display();
	}

	delete player;
	delete window;

	return success;
}

// SUCCESS: loads/draws the debris and moves it
bool Test::testDebris()
{
	bool success = false;

	float width = 800;
	float height = 800;

	std::vector<Debris> debris;

	float spawnTimerMax = 10.f;
	float spawnTimer = spawnTimerMax;
	int maxDebris = 15;

	sf::Event event;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Debris Test", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60); // so frame rate doesn't get too high

	while (window->isOpen()) // HIT ESCAPE TO CLOSE THE WINDOW
	{
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: // close window
			{
				window->close(); // manually close the window
				break;
			}
			case sf::Event::KeyPressed: // key is pressed
			{
				if (event.key.code == sf::Keyboard::Escape) // close window if Escape is pressed too
				{
					window->close();
				}
				break;
			}
			}
		}

		// spawn debris
		if (spawnTimer < spawnTimerMax)
		{
			spawnTimer += 1.f;
		}
		else
		{
			if (debris.size() < maxDebris)
			{
				debris.push_back(Debris(*window));
				spawnTimer = 0.f;
			}
		}

		// update debris
		for (size_t i = 0; i < debris.size(); i++) // check all the Debris
		{
			debris[i].update(window);
		}

		window->clear();

		// render debris
		for (auto i : debris)
		{
			i.render(*window); // render Debris
		}

		window->display();

		if (!debris.empty())
		{
			success = true;
		}
	}

	delete window;

	return success;
}

// SUCCESS: tests the actual function of the game (i.e moving the sprite to the top without touching any debris)
bool Test::testGameLoop()
{
	bool success = false;

	Game game;

	while (game.isRunning())
	{
		// UPDATE
		game.update();

		// RENDER
		game.render();

		success = true; // if we've made it this far, we're probably successful
	}

	return success;
}

// SUCCESS: creates the starting menu and checks if it reads inputs correctly
bool Test::testMenu()
{
	bool success = false;

	Menu menu;
	sf::Event event;

	while (menu.menuWindow->isOpen())
	{
		while (menu.menuWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				{
					menu.MoveSelectionUp();
					break;
				}
				case sf::Keyboard::S:
				{
					menu.MoveSelectionDown();
					break;
				}
				case sf::Keyboard::Return:
				{
					success = true; // if we can select options, it's successful

					switch (menu.selectedItemIndex)
					{
					case 0: // play
					{
						std::cout << "Play Game selected" << std::endl;
						break;
					}
					case 1:
					{
						std::cout << "Exit Game selected" << std::endl;
						menu.menuWindow->close();
						break;
					}
					}
					break;
				}
				case sf::Keyboard::Escape:
				{
					menu.menuWindow->close();
					break;
				}
				}
				success = true;
			}
			}
		}
		menu.menuWindow->clear();
		menu.render(*menu.menuWindow);
		menu.menuWindow->display();
	}

	return success;
}

#include"Game.h"


Game::Game()
{
	initVariables(); // variables must be set first
	initWindow();
	initFont();
	initText();

	startX = (window->getSize().x - player.getSprite()->getGlobalBounds().width) / 2; // true center X
	startY = window->getSize().y - player.getSprite()->getGlobalBounds().height - 20; // bottom of window
	player.setPos(startX, startY); // set the player at the start point
}

Game::~Game()
{
	delete window;
}

// get user input
void Game::pollEvents()
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
}

// updates game logic
void Game::update()
{
		pollEvents(); // get user input
		spawnDebris(); // spawn Debris
		player.update(window); // update the player
		updateCollision(); // check for collisions
		updateText();
}

// visualizing the game logic
void Game::render()
{
	// clear old frame
	window->clear(); // R, G, B, Transparency || input a default Color

	// draw new frame
	player.render(window); // render player

	for (auto i : debris)
	{
		i.render(*window); // render Debris
	}

	// render text
	renderText();

	window->display(); // window is done drawing

}

void Game::spawnDebris()
{
	// timer
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

}

void Game::updateCollision()
{
	// check for collision
	for (size_t i = 0; i < debris.size(); i++) // check all the Debris
	{
		if (player.getSprite()->getGlobalBounds().intersects(debris[i].getGlobalBounds()))
		{
			player.setPos(startX, startY); // set player back to starting position
			player.setHP(player.getHP() - 1); // decrement hp

		}
		else // keep the balls moving
		{
			debris[i].update(this->window);
		}
	}
}

void Game::updateText()
{
	std::stringstream ss;

	ss << " Score: " << player.getPoints() << "\n" << " Lives: " << player.getHP(); // set it to the number of points

	guiText.setString(ss.str());
}

void Game::renderText()
{
	window->draw(guiText);
}

bool Game::isGameOver()
{
	if (player.getHP() == 0)
	{
		return true;
	}
	return false;
}

const bool Game::isRunning() const
{
	return window->isOpen();
}

sf::RenderWindow* Game::getWindow()
{
	return window;
}

void Game::initVariables()
{
	window = nullptr;
	spawnTimerMax = 10.f;
	spawnTimer = spawnTimerMax;
	maxDebris = 15;
}

void Game::initWindow()
{
	videoMode.height = 800;
	videoMode.width = 800;

	window = new sf::RenderWindow(videoMode, "Get to the other side!", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60); // so frame rate doesn't get too high
}

void Game::initText()
{
	guiText.setFont(font);
	guiText.setFillColor(sf::Color::White);
	guiText.setCharacterSize(100);
	guiText.setPosition(0.f, window->getSize().y - 200);
}

void Game::initFont()
{
	if (!font.loadFromFile("Fonts/game_over.ttf"))
	{
		std::cout << "Font file not loaded" << std::endl;
	}
}

void Game::storeHighScore()
{
	file.open("highscore.txt", std::ios::in);

	if (file.peek() == std::fstream::traits_type::eof() ||
		(file.peek()-48) < player.getPoints()) // either file is empty or the highscore is less than the new highscore
	{
		file.close();
		file.open("highscore.txt", std::ios::out);
		file << player.getPoints();
	}
	file.close();
}

std::string Game::getHighScore()
{
	std::string highscore;
	file.open("highscore.txt", std::ios::in);
	getline(file, highscore);
	file.close();
	return highscore;
}
#pragma once



#include"Player.h"
#include"Debris.h"
#include"Menu.h"

#include<vector>
#include<sstream>
#include<fstream>

/*
Game acts as wrapper class for game
*/

class Game
{
public:
	Game();
	virtual ~Game();

	// member functions
	void pollEvents();
	void spawnDebris();

	void update();
	void updateCollision();
	void updateText();

	void render();
	void renderText();


	// accessors
	const bool isRunning() const;
	sf::RenderWindow* getWindow();
	std::string getHighScore();
	bool isGameOver();

	// modifiers
	void storeHighScore();


private:
	// private functions
	void initVariables();
	void initWindow();
	void initText();
	void initFont(); 

	// variables
	sf::RenderWindow* window; // window ptr
	sf::VideoMode videoMode; // window mode variable
	sf::Event event; // event variable
	bool endGame;

	// Game Objects
	Player player;
	float startX;
	float startY;

	std::vector<Debris> debris;
	float spawnTimerMax;
	float spawnTimer;
	int maxDebris;

	sf::Font font;
	sf::Text guiText;

	std::fstream file;

	friend class Test;
};

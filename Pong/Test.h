#pragma once
#include"Menu.h"

class Test
{
public:
	Test();
	~Test();

	void runTests(); // runs all the test cases

private:
	// 5 test cases
	bool testRenderWindow(); // tests opening a window
	bool testPlayer(); // tests creating a player object in a window and updating position
	bool testDebris(); // tests creating debris objects in a window, and updating positions
	bool testGameLoop(); // tests entire game loop
	bool testMenu(); // tests the main menu operation
};


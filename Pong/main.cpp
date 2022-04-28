/*
Programmer: Robin Samson, Silas Peterson, Adrian Peregrino

Class: CptS 122, Spring 2022; Lab Section 1

Programming Assignment: PA9, Graphical Game or Application

Description: This program runs an arcade-style game inspired by Space Race (1977) using SFML for graphics implementations. It's pretty fun :)
*/


#include"Test.h" // includes all header files


int main()
{
	// initialize random seed
	srand(static_cast<unsigned>(time(0)));

	// run tests
	Test test;
	test.runTests();

	// play game-> menu controls the game
	Menu menu;
	menu.runGame();

	return 0;
}
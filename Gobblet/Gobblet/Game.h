
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
//#include "Player.h"
#include "Player2.h"
#include "AI.h"
#include "Grid.h"
//#include "GameState.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	/// <summary>
	/// here we set up the player 
	/// 1/2/3 is all three sets of all goblets e.g one has 4 goblets in it
	/// </summary>
	Player myPlayer[3];
	/// <summary>
	/// here we set up the Ai 
	/// 1/2/3 is all three sets of all goblets e.g one has 4 goblets in it
	/// </summary>
	AI AiEnemy[3];
	/// <summary>
	/// Here we include out grind to the game.h 
	/// </summary>
	Grid myGrid;

	/// <summary>
	/// this is a temp number to make sure we can only grab one single item from all the sets 
	/// </summary>
	int temp = 0;

	//GameState state;
	const int MAX_DEPTH = 5; // maximum depth of the minimax search

	bool playerTurn = false;


	void enemiesGo();
	int randomValue;
	int randomValue2;

	void getbestMove();
private:
	/// <summary>
	/// this is a process events function which will run through all the events
	/// </summary>
	void processEvents();

	/// <summary>
	/// here is the gupdate function for the game, this function will check other updates such as player or ai and will update the game
	/// </summary>
	void update(sf::Time t_deltaTime);
	/// <summary>
	/// here we pass all the other classes the render window to be a ble to render inside the game
	/// </summary>
	void render();
	/// <summary>
	/// here we set the poistions of the sets and pieces for the player and Ai
	/// </summary>
	void setStartPos();
	/// <summary>
	/// this fucniton allows us to snap the currently holding piece to the square that we are hovering over 
	/// </summary>
	void snapGobletsToSquare(int i);

	/// <summary>
	/// here we check if the mouse is going to be pressed and checks what are we clicking on.
	/// </summary>
	void mouseCheckGrab();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game
	bool cannotGrab = false;
};

#endif 


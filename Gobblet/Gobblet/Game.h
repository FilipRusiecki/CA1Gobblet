
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "AI.h"
#include "Grid.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	Player myPlayer[3]; // 1/2/3 is all three sets of all goblets e.g one has 4 goblets in it
	AI AiEnemy[3];// 1/2/3 is all three sets of all goblets e.g one has 4 goblets in it
	Grid myGrid;


private:
	void processEvents();
	void processKeys(sf::Event t_event);

	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif 


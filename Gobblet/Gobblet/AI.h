
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
/// <summary>
/// this is class for AI, here we controll the AI as required
/// </summary>
class AI {
public:
	/// <summary>
	/// making an array of circle shapes for 3 sets 
	/// </summary>
	sf::CircleShape AiGob[4];



	AI();
	void update(sf::RenderWindow& t_window, sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpGoblet();
	// here we check the mouse post

private:

};
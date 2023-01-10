#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
public:
	//one set of gobblets there is 4 in one set.... we need 3 sets 
	sf::CircleShape gob[4];


	// mouse pos
	sf::CircleShape mousePos;

	bool m_isGobGrabbed = false;

	Player();
	void update(sf::RenderWindow& t_window, sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpGoblet();
	// here we check the mouse post
	void mouseCheckGrab();

private:

};
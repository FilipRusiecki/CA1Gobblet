#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
public:
	//one set of gobblets there is 4 in one set.... we need 3 sets 
	sf::CircleShape gob[4];
	bool gobGrabbed[4];

	// mouse pos
	sf::CircleShape mousePos;

	bool m_isGobGrabbed = false;

	bool cannotGrab = false;

	bool gob4isGrabbed = false;
	bool gob3isGrabbed = false;
	bool gob2isGrabbed = false;
	bool gob1isGrabbed = false;


	Player();
	void update(sf::RenderWindow& t_window, sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpGoblet();
	// here we check the mouse post
	void mouseCheckGrab();

private:

};
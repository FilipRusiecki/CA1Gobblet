#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Player2 {
public:
	//one set of gobblets there is 4 in one set.... we need 3 sets 
	sf::CircleShape gob1[12];
	bool gobGrabbed[12];

	int temp = 15;


	sf::CircleShape gob2[4];
	sf::CircleShape gob3[4];


	// mouse pos
	sf::CircleShape mousePos;

	bool m_isGobGrabbed = false;

	bool cannotGrab = false;

	bool gob4isGrabbed = false;
	bool gob3isGrabbed = false;
	bool gob2isGrabbed = false;
	bool gob1isGrabbed = false;


	Player2();
	void update(sf::RenderWindow& t_window, sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpGoblet();
	// here we check the mouse post
	void mouseCheckGrab();

private:

};
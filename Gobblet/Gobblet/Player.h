#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
public:
	/// <summary>
	/// making an array of circle shapes for 3 sets 
	/// </summary>
	sf::CircleShape gob[4];
	bool gobGrabbed[4];

	/// <summary>
	/// This is a circle shape that is attached to mouse position for interaction purpose
	/// </summary>
	sf::CircleShape mousePos;
	/// <summary>
	/// This bool is for checking if a piece is grabbed 
	/// </summary>
	bool m_isGobGrabbed = false;
	/// <summary>
	/// this bool is for checking if we currently can grab or not
	/// </summary>
	bool cannotGrab = false;
	/// <summary>
	/// here are the bool to check if one of the pieces is grabbed or not by the player
	/// </summary>
	bool gob4isGrabbed = false;
	bool gob3isGrabbed = false;
	bool gob2isGrabbed = false;
	bool gob1isGrabbed = false;


	Player();
	/// <summary>
	/// here is the update function of the player where we update all necessary things for our player
	/// </summary>
	void update(sf::RenderWindow& t_window, sf::Time t_deltaTime);
	/// <summary>
	/// here is the render function of the player where we render all parts of the player 
	/// </summary>
	void render(sf::RenderWindow& t_window);
	/// <summary>
	/// this function is to setup all the pieces in their sets up to be ready for play
	/// </summary>
	void setUpGoblet();
	// here we check the mouse post
	void mouseCheckGrab();

private:

};
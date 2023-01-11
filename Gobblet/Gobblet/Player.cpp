#include "Player.h"

Player::Player()
{	
	setUpGoblet();
}





void Player::setUpGoblet()
{
	gob[0].setRadius(30); // SMALLEST 
	gob[1].setRadius(45); // MEDIUM
	gob[2].setRadius(60); // BIG
	gob[3].setRadius(80); // LARGE

	for (int i = 0; i < 4; i++)
	{
		gob[i].setFillColor(sf::Color::White);
		gob[i].setOrigin(gob[i].getRadius() , gob[i].getRadius() );
		gob[i].setOutlineThickness(5.0f);
		gob[i].setOutlineColor(sf::Color::Magenta);


	}
	//gob[0].setPosition(100, 100);// SMALLEST 
	//gob[1].setPosition(100, 300);// MEDIUM
	//gob[2].setPosition(100, 450);// BIG
	//gob[3].setPosition(100, 750);// LARGE

	mousePos.setRadius(10.0f);
	mousePos.setFillColor(sf::Color::Red);
	mousePos.setOrigin(5.0f, 5.0f);
}

void Player::update(sf::RenderWindow& t_window, sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(t_window); //Get mouse position
	mousePos.setPosition(mousePosition.x, mousePosition.y);
	//std::cout << mousePosition.x  << " " << mousePosition.y  << std::endl;
}

void Player::render(sf::RenderWindow& t_window)
{

	t_window.draw(mousePos);
	
	for (int i = 0; i < 4; i++)
	{
		t_window.draw(gob[i]);
	}
}

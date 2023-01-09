#include "Player.h"

Player::Player()
{	
	for(int i = 0; i <4;i++)
	{
		gob[i].setFillColor(sf::Color::White);
	}




	mousePos.setRadius(10.0f);
	mousePos.setFillColor(sf::Color::Red);
	mousePos.setOrigin(5.0f, 5.0f);
}

void Player::update(sf::RenderWindow& t_window, sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(t_window); //Get mouse position
	mousePos.setPosition(mousePosition.x, mousePosition.y);
	std::cout << mousePosition.x  << " " << mousePosition.y  << std::endl;

}

void Player::render(sf::RenderWindow& t_window)
{

	for (int i = 0; i < 4; i++)
	{
		t_window.draw(gob[i]);
	}

	t_window.draw(mousePos);
}

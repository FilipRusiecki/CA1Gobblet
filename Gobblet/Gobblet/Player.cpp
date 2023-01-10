#include "Player.h"

Player::Player()
{	
	setUpGoblet();
}





void Player::setUpGoblet()
{
	gob[0].setRadius(30);
	gob[1].setRadius(45);
	gob[2].setRadius(70);
	gob[3].setRadius(90);

	for (int i = 0; i < 4; i++)
	{
		gob[i].setFillColor(sf::Color::White);
		//gob[i].setPosition(100, 100);
		gob[i].setOrigin(gob[i].getRadius() , gob[i].getRadius() );


	}

	gob[0].setPosition(100, 100);
	gob[1].setPosition(100, 300);
	gob[2].setPosition(100, 450);
	gob[3].setPosition(100, 750);




	mousePos.setRadius(10.0f);
	mousePos.setFillColor(sf::Color::Red);
	mousePos.setOrigin(5.0f, 5.0f);
}

void Player::mouseCheckGrab()
{
	if (mousePos.getGlobalBounds().intersects(gob[3].getGlobalBounds()) )// HERE IS THE CHECK FIOR  LARGE CIRCLE
	{
		std::cout << "collided with smallest" << std::endl;
		// grab the thing here 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false)
		{
			gob[3].setPosition(mousePos.getPosition());

		}
	}
	
	else if (mousePos.getGlobalBounds().intersects(gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  BIG CIRCLE
	{
		std::cout << "collided with second" << std::endl;
		// grab the thing here 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false)
		{
			gob[2].setPosition(mousePos.getPosition());

		}
	}

	else if (mousePos.getGlobalBounds().intersects(gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR SECOND MEDIOUM CIRCLE
	{
		std::cout << "collided with big" << std::endl;
		// grab the thing here 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false)
		{
			gob[1].setPosition(mousePos.getPosition());

		}
	}

	else if (mousePos.getGlobalBounds().intersects(gob[0].getGlobalBounds())) // HERE IS THE CHECK FIOR SMALLER CIRCLE
	{
		std::cout << "collided with large" << std::endl;
		// grab the thing here 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false)
		{
			gob[0].setPosition(mousePos.getPosition());

		}
	}



	
}

void Player::update(sf::RenderWindow& t_window, sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(t_window); //Get mouse position
	mousePos.setPosition(mousePosition.x, mousePosition.y);
	std::cout << mousePosition.x  << " " << mousePosition.y  << std::endl;
	mouseCheckGrab();
}

void Player::render(sf::RenderWindow& t_window)
{

	t_window.draw(mousePos);
	
	for (int i = 0; i < 4; i++)
	{
		t_window.draw(gob[i]);
	}
}

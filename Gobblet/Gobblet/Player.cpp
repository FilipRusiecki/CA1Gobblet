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

//void Player::mouseCheckGrab()
//{
//	if (mousePos.getGlobalBounds().intersects(gob[3].getGlobalBounds()) )// HERE IS THE CHECK FIOR  LARGE CIRCLE
//	{
//		//std::cout << "collided with smallest" << std::endl;
//		// grab the thing here 
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false && gob3isGrabbed == false && gob2isGrabbed == false && gob1isGrabbed == false)
//		{
//		
//			gob[3].setPosition(mousePos.getPosition());
//			gob4isGrabbed = true;
//		}
//		//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//		//{
//		//	gob4isGrabbed = false;
//		//}
//	}
//	
//	else if (mousePos.getGlobalBounds().intersects(gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  BIG CIRCLE
//	{
//		//std::cout << "collided with second" << std::endl;
//		// grab the thing here 
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false  && cannotGrab == false&& gob4isGrabbed == false && gob2isGrabbed == false && gob1isGrabbed == false)
//		{
//
//			gob[2].setPosition(mousePos.getPosition());
//			gob3isGrabbed = true;
//		}
//		//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//		//{
//		//	gob3isGrabbed = false;
//		//	
//		//}
//	}
//
//	else if (mousePos.getGlobalBounds().intersects(gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR SECOND MEDIOUM CIRCLE
//	{
//		//std::cout << "collided with big" << std::endl;
//		// grab the thing here 
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false && gob4isGrabbed == false && gob3isGrabbed == false && gob1isGrabbed == false)
//		{
//			gob[1].setPosition(mousePos.getPosition());
//			gob2isGrabbed = true;
//		}
//		//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//		//{
//		//	gob2isGrabbed = false;
//		//	
//		//}
//	}
//
//	else if (mousePos.getGlobalBounds().intersects(gob[0].getGlobalBounds())) // HERE IS THE CHECK FIOR SMALLER CIRCLE
//	{
//		//std::cout << "collided with large" << std::endl;
//		// grab the thing here 
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false  && gob4isGrabbed == false && gob3isGrabbed == false && gob2isGrabbed == false)
//		{
//			gob[0].setPosition(mousePos.getPosition());
//			gob1isGrabbed = true;
//		}
//		//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//		//{
//		//	
//
//		//}
//	}
//	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
//	{
//		
//		gob4isGrabbed = false;
//		gob3isGrabbed = false;
//		gob2isGrabbed = false;
//		gob1isGrabbed = false;
//	}
//}

void Player::update(sf::RenderWindow& t_window, sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(t_window); //Get mouse position
	mousePos.setPosition(mousePosition.x, mousePosition.y);
	//std::cout << mousePosition.x  << " " << mousePosition.y  << std::endl;
	//mouseCheckGrab();
}

void Player::render(sf::RenderWindow& t_window)
{

	t_window.draw(mousePos);
	
	for (int i = 0; i < 4; i++)
	{
		t_window.draw(gob[i]);
	}
}

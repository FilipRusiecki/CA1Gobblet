#include "Player2.h"

Player2::Player2()
{
	setUpGoblet();
}





void Player2::setUpGoblet()
{


	for (int i = 0; i < 12; i++)
	{
		gob1[i].setFillColor(sf::Color::White);
		gob1[i].setOrigin(gob1[i].getRadius(), gob1[i].getRadius());
		gob1[i].setOutlineThickness(5.0f);
		gob1[i].setOutlineColor(sf::Color::Magenta);

		gobGrabbed[i] = false;

		//gob1[i].setFillColor(sf::Color::White);
		//gob1[i].setOrigin(gob2[i].getRadius(), gob2[i].getRadius());
		//gob2[i].setOutlineThickness(5.0f);
		//gob2[i].setOutlineColor(sf::Color::Magenta);

		//gob3[i].setFillColor(sf::Color::White);
		//gob3[i].setOrigin(gob3[i].getRadius(), gob3[i].getRadius());
		//gob3[i].setOutlineThickness(5.0f);
		//gob3[i].setOutlineColor(sf::Color::Magenta);
	}


	gob1[0].setRadius(30); // SMALLEST 
	gob1[1].setRadius(45); // MEDIUM
	gob1[2].setRadius(60); // BIG
	gob1[3].setRadius(80); // LARGE

	gob1[0].setPosition(30, 100);// SMALLEST 
	gob1[1].setPosition(30, 100);// MEDIUM
	gob1[2].setPosition(30, 100);// BIG
	gob1[3].setPosition(30, 100);// LARGE



	gob1[4].setRadius(30); // SMALLEST 
	gob1[5].setRadius(45); // MEDIUM
	gob1[6].setRadius(60); // BIG
	gob1[7].setRadius(80); // LARGE

	gob1[4].setPosition(30, 300);// SMALLEST 
	gob1[5].setPosition(30, 300);// MEDIUM
	gob1[6].setPosition(30, 300);// BIG
	gob1[7].setPosition(30, 300);// LARGE




	gob1[8].setRadius(30); // SMALLEST 
	gob1[9].setRadius(45); // MEDIUM
	gob1[10].setRadius(60); // BIG
	gob1[11].setRadius(80); // LARGE

	gob1[8].setPosition(30, 500);// SMALLEST 
	gob1[9].setPosition(30, 500);// MEDIUM
	gob1[10].setPosition(30, 500);// BIG
	gob1[11].setPosition(30, 500);// LARGE





	mousePos.setRadius(10.0f);
	mousePos.setFillColor(sf::Color::Red);
	mousePos.setOrigin(5.0f, 5.0f);
}



void Player2::update(sf::RenderWindow& t_window, sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(t_window); //Get mouse position
	mousePos.setPosition(mousePosition.x, mousePosition.y);
	//std::cout << mousePosition.x  << " " << mousePosition.y  << std::endl;
	mouseCheckGrab();
}

void Player2::render(sf::RenderWindow& t_window)
{

	t_window.draw(mousePos);

	for (int i = 0; i < 12; i++)
	{
		t_window.draw(gob1[i]);
		//t_window.draw(gob2[i]);
		//t_window.draw(gob3[i]);

	}
}


void Player2::mouseCheckGrab()
{
	
	for (int s1 = 0; s1 < 12; s1++)
	{

		if (mousePos.getGlobalBounds().intersects(gob1[s1].getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
		
			gobGrabbed[s1] = true;
			if (gobGrabbed[s1] == true)
			{
				gob1[s1].setPosition(mousePos.getPosition().x - gob1[s1].getRadius(), mousePos.getPosition().y - gob1[s1].getRadius());

				//if (mousePos.getGlobalBounds().intersects(gob1[s1].getGlobalBounds()) && gobGrabbed[s1] == false)
				//{
					//ignore the other circles 
				//}
			}
			for (int ss1 = 0; ss1 < 12; ss1++)
			{
				if (gobGrabbed[ss1] == true)
				{
					gobGrabbed[s1] = false;
					break;
				}
			
			}
			//std::cout << " set 1 " << std::endl;

		}






		//if (mousePos.getGlobalBounds().intersects(gob1[s2].getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		//{

		//	gobGrabbed[s2] = true;
		//	gob1[s2].setPosition(mousePos.getPosition().x - gob1[s2].getRadius(), mousePos.getPosition().y - gob1[s2].getRadius());

		//	for (int ss1 = 0; ss1 < 12; ss1++)
		//	{
		//		if (gobGrabbed[ss1] == true)
		//		{
		//			break;
		//		}

		//	}
		//	std::cout << " set 2 " << std::endl;
		//}




		//if (mousePos.getGlobalBounds().intersects(gob1[s3].getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		//{

		//	gobGrabbed[s3] = true;
		//	gob1[s3].setPosition(mousePos.getPosition().x - gob1[s3].getRadius(), mousePos.getPosition().y - gob1[s3].getRadius());
		//	for (int ss1 = 8; ss1 < 12; ss1++)
		//	{
		//		if (gobGrabbed[ss1] == true)
		//		{
		//			break;
		//		}

		//	}
		//	std::cout << " set 3 " << std::endl;
		//}
	}
	



		//if (mousePos.getGlobalBounds().intersects(gob2[p].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		//{


		//	std::cout << " set 2 " << std::endl;


		//	//std::cout << "collided with smallest" << std::endl;
		//	// grab the thing here 
		//		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false && gob3isGrabbed == false && gob2isGrabbed == false && gob1isGrabbed == false)
		//		//{

		//		//	gob[3].setPosition(mousePos.getPosition());
		//		//	gob4isGrabbed = true;
		//		//}
		//	//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//	//{
		//	//	gob4isGrabbed = false;
		//	//}
		//}
		//if (mousePos.getGlobalBounds().intersects(gob3[p].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		//{


		//	std::cout << " set 3 " << std::endl;


		//	//std::cout << "collided with smallest" << std::endl;
		//	// grab the thing here 
		//		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isGobGrabbed == false && gob3isGrabbed == false && gob2isGrabbed == false && gob1isGrabbed == false)
		//		//{

		//		//	gob[3].setPosition(mousePos.getPosition());
		//		//	gob4isGrabbed = true;
		//		//}
		//	//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//	//{
		//	//	gob4isGrabbed = false;
		//	//}
		//}



	
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		for (int gr = 0; gr < 12; gr++)
		{
			gobGrabbed[gr] = false;
			std::cout << "relased " << std::endl;
		}
	}
}
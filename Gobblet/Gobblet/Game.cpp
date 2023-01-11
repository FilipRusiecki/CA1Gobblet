#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1200, 1000,  sf::VideoMode::getDesktopMode().bitsPerPixel }, "Gobblet" },
	m_exitGame{ false } //when true game will exit
{

	setStartPos();


}


Game::~Game() 
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{

}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	for (int i = 0; i < 16; i++) 
	{
		for (int k = 0; k < 3; k++)
		{

			if (myPlayer[k].mousePos.getGlobalBounds().intersects(myGrid.interactable[i].getGlobalBounds()))
			{
				// set color of square to red when mouse hovers over
				myGrid.interactable[i].setFillColor(sf::Color::Red);
			}
			else
			{
				myGrid.interactable[i].setFillColor(sf::Color::Green);
			}
			if (myGrid.occupied[i] == true)
			{
				myGrid.interactable[i].setFillColor(sf::Color::Blue);
			}
			snapGobletsToSquare(i);
		}
	}
	myPlayer[0].update(m_window, t_deltaTime);
	myPlayer[1].update(m_window, t_deltaTime);
	myPlayer[2].update(m_window, t_deltaTime);

	//myPlayer2.update(m_window, t_deltaTime);
	AiEnemy[0].update(m_window, t_deltaTime);
	AiEnemy[1].update(m_window, t_deltaTime);
	AiEnemy[2].update(m_window, t_deltaTime);

	myGrid.update(m_window, t_deltaTime);



	//for (int k = 0; k < 3; k++) // controls main set of pieces
	//{
	//	for (int j = 0; j < 4; j++) // copntrols size of pieces grabbed
	//	{
	//		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	//		{
	//			if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
	//			{
	//				myPlayer[k].gob[3].setPosition(myPlayer[k].mousePos.getPosition());
	//			
	//			}

	//			if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[2].getGlobalBounds()) && cannotGrab == false)// HERE IS THE CHECK FIOR  LARGE CIRCLE
	//			{
	//				myPlayer[k].gob[2].setPosition(myPlayer[k].mousePos.getPosition());
	//				cannotGrab = true;
	//			}

	//			if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[1].getGlobalBounds()) && cannotGrab == false)// HERE IS THE CHECK FIOR  LARGE CIRCLE
	//			{
	//				myPlayer[k].gob[1].setPosition(myPlayer[k].mousePos.getPosition());
	//				cannotGrab = true;
	//			}

	//			if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[0].getGlobalBounds()) && cannotGrab == false)// HERE IS THE CHECK FIOR  LARGE CIRCLE
	//			{
	//				myPlayer[k].gob[0].setPosition(myPlayer[k].mousePos.getPosition());
	//				cannotGrab = true;
	//			}
	//		}
	//	}
	//}




	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		cannotGrab == false;
	}





	mouseCheckGrab();


}

void Game::render()
{
	m_window.clear(sf::Color{ 212, 159, 15 });
	myGrid.render(m_window);
	myPlayer[0].render(m_window);
	myPlayer[1].render(m_window);
	myPlayer[2].render(m_window);

	//myPlayer2.render(m_window);
	AiEnemy[0].render(m_window);
	AiEnemy[1].render(m_window);
	AiEnemy[2].render(m_window);


	m_window.display();
}



void Game::snapGobletsToSquare(int t_i)
{
	for (int k = 0; k < 3; k++) // controls main set of pieces
	{
		for (int j = 0; j < 4; j++) // copntrols size of pieces grabbed
		{
			
			// this makes goblet snap to the square position middle




			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && myPlayer[k].gob[j].getGlobalBounds().intersects(myGrid.interactable[t_i].getGlobalBounds()))
			{
				
					if (myGrid.occupied[t_i] == false)
					{
						std::cout << "SNAP" << std::endl;
						myPlayer[k].gob[j].setPosition(myGrid.interactable[t_i].getPosition().x + 90, myGrid.interactable[t_i].getPosition().y + 90);
						myGrid.occupied[t_i] = true;
					}
					//for (int r = 0; r < 16; r++) // copntrols size of pieces grabbed
					//{
					//	if (myGrid.interactable[t_i].getGlobalBounds().intersects(myGrid.interactable[r].getGlobalBounds()))
					//	{
					//		myPlayer[k].gob[r].setPosition(100, 150);
					//	}
					//}
					//checkIfGobIsBigger();

			}





				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true)
				{
					myGrid.occupied[t_i] = false;
				}

				/*		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && !myPlayer[k].gob[j].getGlobalBounds().intersects(myGrid.interactable[t_i].getGlobalBounds()))
						{
							if (k == 0)
							{
								myPlayer[k].gob[j].setPosition(100, 150);
							}
						}*/

						//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && myPlayer[k].gob[j].getGlobalBounds().intersects(myGrid.interactable[i].getGlobalBounds()) == false)
						//{
						//	// put goblet in its old position

						//	if (k == 0)
						//	{
						//		std::cout << "GO BACK" << std::endl;

						//		myPlayer[k].gob[j].setPosition(100, 150);
						//	}

						//}
			
		}
	}
}

void Game::checkIfGobIsBigger()
{

	for (int k = 0; k < 3; k++) // controls main set of pieces
	{
		for (int j = 0; j < 4; j++) // copntrols size of pieces grabbed
		{

		}
	}
}






void Game::setStartPos() 
{
	myPlayer[0].gob[0].setPosition(100, 150);
	myPlayer[0].gob[1].setPosition(100, 150);
	myPlayer[0].gob[2].setPosition(100, 150);
	myPlayer[0].gob[3].setPosition(100, 150);

	myPlayer[1].gob[0].setPosition(100, 450);
	myPlayer[1].gob[1].setPosition(100, 450);
	myPlayer[1].gob[2].setPosition(100, 450);
	myPlayer[1].gob[3].setPosition(100, 450);

	myPlayer[2].gob[0].setPosition(100, 750);
	myPlayer[2].gob[1].setPosition(100, 750);
	myPlayer[2].gob[2].setPosition(100, 750);
	myPlayer[2].gob[3].setPosition(100, 750);

	AiEnemy[0].AiGob[0].setPosition(1100, 150);
	AiEnemy[0].AiGob[1].setPosition(1100, 150);
	AiEnemy[0].AiGob[2].setPosition(1100, 150);
	AiEnemy[0].AiGob[3].setPosition(1100, 150);

	AiEnemy[1].AiGob[0].setPosition(1100, 450);
	AiEnemy[1].AiGob[1].setPosition(1100, 450);
	AiEnemy[1].AiGob[2].setPosition(1100, 450);
	AiEnemy[1].AiGob[3].setPosition(1100, 450);

	AiEnemy[2].AiGob[0].setPosition(1100, 750);
	AiEnemy[2].AiGob[1].setPosition(1100, 750);
	AiEnemy[2].AiGob[2].setPosition(1100, 750);
	AiEnemy[2].AiGob[3].setPosition(1100, 750);
}









void Game::mouseCheckGrab()
{
	std::cout << temp << std::endl;


	for (int k = 0; k < 3; k++) // controls main set of pieces
	{
		if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{

			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].cannotGrab == false && myPlayer[k].gob3isGrabbed == false && myPlayer[k].gob2isGrabbed == false && myPlayer[k].gob1isGrabbed == false)
			{

				myPlayer[k].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[k].gob4isGrabbed = true;
				temp = 1000;

			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		else if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  BIG CIRCLE
		{
			//std::cout << "collided with second" << std::endl;
			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && temp!= 1000 && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].gob4isGrabbed == false && myPlayer[k].gob2isGrabbed == false && myPlayer[k].gob1isGrabbed == false)
			{

				myPlayer[k].gob[2].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[k].gob3isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob3isGrabbed = false;
			//	
			//}
		}

		else if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR SECOND MEDIOUM CIRCLE
		{
			//std::cout << "collided with big" << std::endl;
			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].gob4isGrabbed == false && myPlayer[k].gob3isGrabbed == false && myPlayer[k].gob1isGrabbed == false)
			{
				myPlayer[k].gob[1].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[k].gob2isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob2isGrabbed = false;
			//	
			//}
		}

		else if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[0].getGlobalBounds())) // HERE IS THE CHECK FIOR SMALLER CIRCLE
		{
			//std::cout << "collided with large" << std::endl;
			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].gob4isGrabbed == false && myPlayer[k].gob3isGrabbed == false && myPlayer[k].gob2isGrabbed == false)
			{
				myPlayer[k].gob[0].setPosition(myPlayer[k].mousePos.getPosition());
				myPlayer[k].gob1isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	

			//}
		}



		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
		{

			myPlayer[k].gob4isGrabbed = false;
			myPlayer[k].gob3isGrabbed = false;
			myPlayer[k].gob2isGrabbed = false;
			myPlayer[k].gob1isGrabbed = false;
			myPlayer[0].cannotGrab = false;
			myPlayer[1].cannotGrab = false;
			myPlayer[2].cannotGrab = false;

			temp = 0;






		}
	}



	///////////////////////////////////////////////////////////////	///////////////////////////////////////////////////////////////	///////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////
	//if (myPlayer[0].gob4isGrabbed)
	//{
	//	myPlayer[1].cannotGrab = true;
	//	std::cout << myPlayer[1].cannotGrab << std::endl;

	//}
	//std::cout << myPlayer[1].cannotGrab << std::endl;

	//if (myPlayer[1].gob3isGrabbed)
	//{
	//	std::cout << myPlayer[1].cannotGrab << std::endl;

	//	std::cout << "GRABBED" << std::endl;

	//}


	// set TWO interacts with set ONE 

	if (myPlayer[1].gob3isGrabbed)
	{
		if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[0].cannotGrab = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[1].gob4isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}



		if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[1].gob4isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[1].gob4isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////

	}

	// set THREE interacts with set ONE 

	if (myPlayer[2].gob3isGrabbed)
	{
		if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[2].gob4isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}
		if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[2].gob4isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[2].gob4isGrabbed = true;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
	}



	


	if (myPlayer[0].gob3isGrabbed)
	{

		// set ONE interacts with set TWO 

		if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			std::cout << "HAPPENED" << std::endl;

			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED MOREEEEEEEEEEEEEEEEE" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}


		if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 

			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
	}


	// set ONE interacts with set THREE 

	if (myPlayer[2].gob3isGrabbed)
	{

		if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			std::cout << "HAPPENED" << std::endl;

			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED MOREEEEEEEEEEEEEEEEE" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}


		if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 

			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
	}



	// set TWO interacts with set THREE 

	if (myPlayer[1].gob3isGrabbed)
	{
		if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			std::cout << "HAPPENED" << std::endl;

			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED MOREEEEEEEEEEEEEEEEE" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}


		if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 

			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////

	}

		// set THREE interacts with set TWO 
	if (myPlayer[2].gob3isGrabbed)
	{

		if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			std::cout << "HAPPENED" << std::endl;

			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[2].gob4isGrabbed = true;
				std::cout << "HAPPENED MOREEEEEEEEEEEEEEEEE" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}


		if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 

			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[2].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			//std::cout << "collided with smallest" << std::endl;
			// grab the thing here 
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{

				//myPlayer[0].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[2].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
			//if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			//{
			//	gob4isGrabbed = false;
			//}
		}

		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////
	}

}


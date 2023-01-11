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


/// <summary>
/// This allows the game loop to continuesly keep running
/// </summary>
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
/// <summary>
/// this Game function goes through events and make sure they happpen
/// </summary>
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
		
		}
	}
}




/// <summary>
/// here we updated the whole game and everything that needs to be updated from all the classes
/// </summary>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	/// <summary>
	/// This loop goes throguh all the cells on the grid that are interactable with the mouse
	/// </summary>
	/// <param name="t_deltaTime"></param>
	for (int i = 0; i < 16; i++) 
	{
		for (int k = 0; k < 3; k++)
		{

			/// <summary>
			/// if the mouse is hovering over the box, the box will be coloured red 
			/// </summary>
			if (myPlayer[k].mousePos.getGlobalBounds().intersects(myGrid.interactable[i].getGlobalBounds()))
			{
				// set color of square to red when mouse hovers over
				myGrid.interactable[i].setFillColor(sf::Color::Red);
			}
			/// <summary>
			/// when the mouse is not hovering over the box the box will be coloured green.
			/// </summary>
			else
			{
				myGrid.interactable[i].setFillColor(sf::Color::Green);
			}
			/// <summary>
			/// When there is piece placed on the specific box it will be coloured blue to show that its occupied
			/// </summary>
			if (myGrid.occupied[i] == true)
			{
				myGrid.interactable[i].setFillColor(sf::Color::Blue);
			}
			/// <summary>
			/// this fucniton allows us to snap the currently holding piece to the square that we are hovering over 
			/// </summary>
			snapGobletsToSquare(i);
		}
	}
	/// <summary>
	/// updating the player and its pieces
	/// </summary>
	myPlayer[0].update(m_window, t_deltaTime);
	myPlayer[1].update(m_window, t_deltaTime);
	myPlayer[2].update(m_window, t_deltaTime);

	/// <summary>
	/// updating the AI and its pieces
	/// </summary>
	AiEnemy[0].update(m_window, t_deltaTime);
	AiEnemy[1].update(m_window, t_deltaTime);
	AiEnemy[2].update(m_window, t_deltaTime);

	/// <summary>
	/// updating the gird and cells 
	/// </summary>
	myGrid.update(m_window, t_deltaTime);


	/// <summary>
	/// when the button is not pressed here we check and turn off the necessary bools to false
	/// </summary>
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		cannotGrab == false;
	}




	/// <summary>
	/// here in this fucntion we check what is being grabbed and hovered over by the mouse 
	/// </summary>
	mouseCheckGrab();


}
/// <summary>
/// this function renders everything thats necessary such as Grid, Player and AI
/// </summary>
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


/// <summary>
/// this function allows us to snap pieces into the grid
/// </summary>
/// <param name="t_i"></param>
void Game::snapGobletsToSquare(int t_i)
{
	for (int k = 0; k < 3; k++) // controls main set of pieces
	{
		for (int j = 0; j < 4; j++) // copntrols size of pieces grabbed
		{
			
			// this makes goblet snap to the square position middle




			/// <summary>
			/// if mouse button is relased then we allow the snap to happen
			/// </summary>
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && myPlayer[k].gob[j].getGlobalBounds().intersects(myGrid.interactable[t_i].getGlobalBounds()))
			{
				
					if (myGrid.occupied[t_i] == false)
					{
						std::cout << "SNAP" << std::endl;
						myPlayer[k].gob[j].setPosition(myGrid.interactable[t_i].getPosition().x + 90, myGrid.interactable[t_i].getPosition().y + 90);
						myGrid.occupied[t_i] = true;
					}

			}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true)
				{
					myGrid.occupied[t_i] = false;
				}
			
		}
	}
}





/// <summary>
/// this fucntion sets the start pos of each piece and each set
/// </summary>
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









/// <summary>
/// here we will check for the mouse grabbing of certain pieces
/// </summary>
void Game::mouseCheckGrab()
{


	for (int k = 0; k < 3; k++) // controls main set of pieces
	{
		/// <summary>
		/// Here we check if the large piece has been clicked on by the player, if yes we also check if any other piece is grabbed, if any other piece is grabbed we will not allow to hold 2 pieces at same time, other wise  
		/// we set the piece to the mouse location
		/// </summary>
		if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].cannotGrab == false && myPlayer[k].gob3isGrabbed == false && myPlayer[k].gob2isGrabbed == false && myPlayer[k].gob1isGrabbed == false)
			{

				myPlayer[k].gob[3].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[k].gob4isGrabbed = true;
				temp = 1000;

			}
		}
		/// <summary>
		/// Here we check if the big piece has been clicked on by the player, if yes we also check if any other piece is grabbed, if any other piece is grabbed we will not allow to hold 2 pieces at same time, other wise  
		/// we set the piece to the mouse location
		/// </summary>
		else if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  BIG CIRCLE
		{
			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && temp!= 1000 && myPlayer[k].cannotGrab == false && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].gob4isGrabbed == false && myPlayer[k].gob2isGrabbed == false && myPlayer[k].gob1isGrabbed == false)
			{

				myPlayer[k].gob[2].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[k].gob3isGrabbed = true;
			}

		}

		/// <summary>
		/// Here we check if the small piece has been clicked on by the player, if yes we also check if any other piece is grabbed, if any other piece is grabbed we will not allow to hold 2 pieces at same time, other wise  
		/// we set the piece to the mouse location
		/// </summary>
		else if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR SECOND MEDIOUM CIRCLE
		{

			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].cannotGrab == false && myPlayer[k].gob4isGrabbed == false && myPlayer[k].gob3isGrabbed == false && myPlayer[k].gob1isGrabbed == false)
			{
				myPlayer[k].gob[1].setPosition(myPlayer[0].mousePos.getPosition());
				myPlayer[k].gob2isGrabbed = true;
			}

		}
		/// <summary>
		/// Here we check if the tiny piece has been clicked on by the player, if yes we also check if any other piece is grabbed, if any other piece is grabbed we will not allow to hold 2 pieces at same time, other wise  
		/// we set the piece to the mouse location
		/// </summary>
		else if (myPlayer[k].mousePos.getGlobalBounds().intersects(myPlayer[k].gob[0].getGlobalBounds())) // HERE IS THE CHECK FIOR SMALLER CIRCLE
		{
			// grab the thing here 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[k].m_isGobGrabbed == false && myPlayer[k].cannotGrab == false && myPlayer[k].gob4isGrabbed == false && myPlayer[k].gob3isGrabbed == false && myPlayer[k].gob2isGrabbed == false)
			{
				myPlayer[k].gob[0].setPosition(myPlayer[k].mousePos.getPosition());
				myPlayer[k].gob1isGrabbed = true;
			}
		}


		/// <summary>
		/// this function removes all the bools that are blocking the picking up of the pieces when the left click is not clicked
		/// </summary>
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

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// set ONE interacts with set TWO 
	if (myPlayer[0].gob4isGrabbed)
	{
		if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob3isGrabbed = true;
			}
		}
		else if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
		else if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
		else if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}

	}


	if (myPlayer[0].gob3isGrabbed)
	{
		if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			std::cout << "HAPPENED" << std::endl;
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED MOREEEEEEEEEEEEEEEEE" << std::endl;
			}
		}

		else if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			std::cout << "HAPPENED" << std::endl;
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED MOREEEEEEEEEEEEEEEEE" << std::endl;
			}
		}
		else if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
		else if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}


	}

	if (myPlayer[0].gob2isGrabbed)
	{
		if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob3isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob3isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
	}


	if (myPlayer[0].gob1isGrabbed)
	{
		if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}

		else if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob3isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}

		else if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob2isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}

		else if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob2isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}


	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// set ONE interacts with set THREE 

	if (myPlayer[0].gob4isGrabbed)
	{
		if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob3isGrabbed = true;
			}
		}

		else if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;

		}
		else if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
		else if (myPlayer[0].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
	}


	if (myPlayer[0].gob3isGrabbed)
	{
		if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			std::cout << "HAPPENED" << std::endl;
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED MOREEEEEEEEEEEEEEEEE" << std::endl;
			}
		}

		else if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
		else if (myPlayer[0].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}

	}

	if (myPlayer[0].gob2isGrabbed)
	{

		if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}


		else if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}

		else if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[0].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}


	}
	if (myPlayer[0].gob1isGrabbed)
	{

		if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob4isGrabbed = true;
			}
		}


		else if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob3isGrabbed = true;
			}
		}

		else if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob2isGrabbed = true;
			}
		}

		else if (myPlayer[0].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[0].gob2isGrabbed = true;
			}
		}

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// set TWO interacts with set ONE 

	if (myPlayer[1].gob4isGrabbed)
	{
		if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob3isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;

		}
		else if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}
		else if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}

	}


	if (myPlayer[1].gob3isGrabbed)
	{
		if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}

		else if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}
		else if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}


	}
	if (myPlayer[1].gob2isGrabbed)
	{
		if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false &&  myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
	
		}


	}

	if (myPlayer[1].gob1isGrabbed)
	{
		if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}

	}
	


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// set TWO interacts with set THREE 


	if (myPlayer[1].gob4isGrabbed)
	{
		if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob3isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
		else if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
		else if (myPlayer[1].gob[3].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
	}

	if (myPlayer[1].gob3isGrabbed)
	{
		if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
		else if (myPlayer[1].gob[2].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}
	}

	if (myPlayer[1].gob2isGrabbed)
	{
		if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}

		}
		else if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[1].gob[1].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
		}

	}

	if (myPlayer[1].gob1isGrabbed)
	{
		if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
		else if (myPlayer[1].gob[0].getGlobalBounds().intersects(myPlayer[2].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[2].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[1].gob4isGrabbed = true;
				std::cout << "HAPPENED" << std::endl;
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	// set THREE interacts with set ONE 


	if (myPlayer[2].gob4isGrabbed)
	{
		if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob3isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}
		else if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;

		}
		else if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}
	}

	if (myPlayer[2].gob3isGrabbed)
	{
		if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;

		}
		else if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}
	}
	if (myPlayer[2].gob2isGrabbed)
	{

		if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
		}
	}

	if (myPlayer[2].gob1isGrabbed)
	{
		if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[0].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[0].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
	}


		// set THREE interacts with set TWO 

	if (myPlayer[2].gob4isGrabbed)
	{
		if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob3isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
		else if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
		else if (myPlayer[2].gob[3].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
	}

	if (myPlayer[2].gob3isGrabbed)
	{
		if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob2isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}
		else if (myPlayer[2].gob[2].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}

	}

	if (myPlayer[2].gob2isGrabbed)
	{
		if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob1isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[1].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
		}

	}

	if (myPlayer[2].gob1isGrabbed)
	{
		if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[3].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[2].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[1].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
		else if (myPlayer[2].gob[0].getGlobalBounds().intersects(myPlayer[1].gob[0].getGlobalBounds()))// HERE IS THE CHECK FIOR  LARGE CIRCLE
		{
			myPlayer[1].cannotGrab = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && myPlayer[0].m_isGobGrabbed == false && myPlayer[0].gob3isGrabbed == false && myPlayer[0].gob2isGrabbed == false)
			{
				myPlayer[2].gob4isGrabbed = true;
			}
		}
	}
}


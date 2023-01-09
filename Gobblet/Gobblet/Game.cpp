#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1200, 1000,  sf::VideoMode::getDesktopMode().bitsPerPixel }, "Gobblet" },
	m_exitGame{ false } //when true game will exit
{


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

	for (int i = 0; i < 16; i++) // 50 * 50 = 2500
	{
		if (myPlayer.mousePos.getGlobalBounds().intersects(myGrid.interactable[i].getGlobalBounds()))
		{
			 myGrid.interactable[i].setFillColor(sf::Color::Red);
		}
		else
		{
			 myGrid.interactable[i].setFillColor(sf::Color::Green);
		}
	}
	myPlayer.update(m_window, t_deltaTime);
	myGrid.update(m_window, t_deltaTime);

}

void Game::render()
{
	m_window.clear(sf::Color{ 212, 159, 15 });
	myPlayer.render(m_window);
	myGrid.render(m_window);

	m_window.display();
}


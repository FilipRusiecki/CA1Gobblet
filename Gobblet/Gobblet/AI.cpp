#include "AI.h"


AI::AI()
{
	setUpGoblet();
}

void AI::setUpGoblet()
{
	AiGob[0].setRadius(30); // SMALLEST 
	AiGob[1].setRadius(45); // MEDIUM
	AiGob[2].setRadius(60); // BIG
	AiGob[3].setRadius(80); // LARGE

	for (int i = 0; i < 4; i++)
	{
		AiGob[i].setFillColor(sf::Color::Black);
		AiGob[i].setOrigin(AiGob[i].getRadius(), AiGob[i].getRadius());
		AiGob[i].setOutlineThickness(5.0f);
		AiGob[i].setOutlineColor(sf::Color::Magenta);
		aiCanMove[i] = true;
	}
	//gob[0].setPosition(100, 100);// SMALLEST 
	//gob[1].setPosition(100, 300);// MEDIUM
	//gob[2].setPosition(100, 450);// BIG
	//gob[3].setPosition(100, 750);// LARGE
}

void AI::update(sf::RenderWindow& t_window, sf::Time t_deltaTime)
{

}

void AI::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < 4; i++)
	{
		t_window.draw(AiGob[i]);
	}
}

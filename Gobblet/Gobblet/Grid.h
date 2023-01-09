#pragma once
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>
#include <stack>
#include "Player.h"


class Cell {
public:
	Cell();
	~Cell();
	int m_id = 0;
	int m_previousCellId{ -1 };
	bool m_marked = false;
	bool m_isPassable = true;

	int m_centreX = 0;
	int m_centreY = 0;

	float m_h;
	int m_pathCost = -1;
	int myCost = -1;


	bool drawCost = false;
	std::vector<int> m_diagonalList;

	Cell* m_previous;

	Cell(sf::Vector2f t_position, int t_cellID, sf::Font& t_font);
	Cell* previous() const;
	int weight() const;

	void setPrevious(Cell* previous)
	{
		m_previous = previous;
	}
	bool marked() const;
	void setMarked(bool t_marked);
	void addNeighbour(int t_cellID);
	int returnID() const {
		return m_id;
	}
	void render(sf::RenderWindow& t_window);

	sf::Text m_cellcost;
	sf::Font m_fonts;
	int getCost();

	sf::RectangleShape m_shape;

	std::vector<int> m_neighbours;

};

class Grid {
public:
	Grid();
	~Grid();
	Cell& returnCell(int t_id);
	Player myPlayer;
	
	void initialiseMap();
	void update(sf::RenderWindow& t_window, sf::Time t_deltaTime);

	void render(sf::RenderWindow& t_window);

	Cell* findCellPoint(sf::Vector2f point);

	int m = 1;

	std::vector<Cell>& returnAllCells();

	//sf::Text m_cellId[2501];
	sf::Font m_font;
	std::vector<std::vector<Cell>> m_cellsVectorArray;
	std::vector<Cell> m_cellsArray;


	int m_maxRows = 4;
	int m_maxCols = 4;
	int m_currentRow;
	int m_currentCol;
	sf::RectangleShape interactable[16];

private:

};
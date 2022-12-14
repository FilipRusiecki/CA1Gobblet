#include "Grid.h"
Cell::Cell()
{

}

Cell::~Cell()
{
}
/// <summary>
/// In this cell constructor we create a default cell for the grid
/// </summary>
Cell::Cell(sf::Vector2f t_position, int t_cellID, sf::Font& t_font)
{
	//if (!m_fonts.loadFromFile("Assets/Fonts/Pixellari.ttf"))
	//{
	//	std::cout << "error with font file file";
	//}

	m_id = t_cellID;
	m_shape.setSize(sf::Vector2f(800 / 4, 800 / 4));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(1);
	m_shape.setPosition(t_position);
	m_isPassable = true;
	m_previousCellId = -1;


}

Cell* Cell::previous() const
{
	return m_previous;
}


bool Cell::marked() const
{
	return m_marked;
}

void Cell::setMarked(bool t_marked) //bool that is checking if the cell is marked
{
	m_marked = t_marked;
}

void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);

}


int Cell::getCost()
{
	return myCost;
}

void Cell::addNeighbour(int t_cellID) // adding a cell id to the neighbours
{
	m_neighbours.push_back(t_cellID);
}


/// <summary>
/// in Grid constructor we call the initialisemap function to create the grid
/// </summary>
Grid::Grid()
{

	initialiseMap();

}

Grid::~Grid()
{
}


Cell& Grid::returnCell(int t_id)
{
	return m_cellsArray.at(t_id);
}






/// <summary>
/// this function initialises the grid and spawns each cell 
/// </summary>
void Grid::initialiseMap()
{
	srand(time(NULL));

	if (!m_font.loadFromFile("Assets/Fonts/ariblk.ttf"))
	{
		std::cout << "error with font file file";
	}

	sf::Vector2f cellPositions{ 200,50 };
	int count = 0;
	for (int row = 0; row < m_maxRows; row++)
	{

		for (int i = 0; i < m_maxCols; i++)
		{
			Cell cell(cellPositions, count, m_font);

			/// <summary>
			/// adjusting cell position on screen - x axis
			/// </summary>
			cellPositions.x += 800 / 4; 
			if (cellPositions.x >= 900)
			{
				/// <summary>
				/// adjusting cell position on screen - y axis
				/// </summary>
				cellPositions.x = 200;
				cellPositions.y += 800 / 4;

			}

			count++;
			m_cellsArray.push_back(cell);// pushing back the cell
		}
	}
	int p = 0;

	/// <summary>
	/// this loop allows the spawn of the interactable squares that are on the gird
	/// </summary>
	for (int i = 0; i < 16; i++) // 50 * 50 = 2500
	{
		int posY = i / 4;
		int posX = i % 4;

		/// <summary>
		/// here we set the size, colour and position of each square
		/// </summary>
		interactable[i].setSize(sf::Vector2f(180.0f, 180.0f));
		interactable[i].setFillColor(sf::Color::Green);
		interactable[i].setPosition(m_cellsArray.at(i).m_shape.getPosition().x+ 10, m_cellsArray.at(i).m_shape.getPosition().y+10);
		occupied[i] == false;
	}
	m_cellsArray.size();

}

void Grid::update(sf::RenderWindow& t_window, sf::Time t_deltaTime) // update method
{

}


/// <summary>
/// this function returns all the cells.
/// </summary>
std::vector<Cell>& Grid::returnAllCells() // returning all the cells
{
	return m_cellsArray;
}

/// <summary>
/// this function finds a cell at a specific point 
/// </summary>
Cell* Grid::findCellPoint(sf::Vector2f point)
{
	for (int i = 0; i < m_cellsArray.size(); i++)
	{
		if (m_cellsArray.at(i).m_shape.getGlobalBounds().contains(point))
		{
			return &m_cellsArray.at(i);
		}
	}
	return nullptr;
}

/// <summary>
/// this fucntion renders the gird and everything that is inside it. 
/// </summary>
void Grid::render(sf::RenderWindow& t_window) // rendering the grid
{

	for (int index = 0; index < 16; index++)
	{
		m_cellsArray.at(index).render(t_window);
		t_window.draw(interactable[index]);
	}
	

}
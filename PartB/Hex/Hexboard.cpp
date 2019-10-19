#include "HexBoard.h"

HexBoard::HexBoard(int size) : m_size(size), player(COLOR::NONE), computer(COLOR::NONE)
{
	m_board.resize(size, std::vector<Node>(size, Node()));
}

HexBoard::~HexBoard() 
{
	std::cout << "Destructor Called";
}

void HexBoard::startGame()
{
	playerSetup();
	printBoard();
}

// Have user choose to go first or second
void HexBoard::playerSetup()
{
	while (true)
	{
		std::cout << "Choose a color: Enter 'w' for White (goes first) or 'b' for Black (goes second)" << std::endl;
		std::string input;
		std::cin >> input;

		if (input.compare("w"))
		{
			player = COLOR::WHITE;
			computer = COLOR::BLACK;
			return;
		}
		else if (input.compare("b"))
		{
			player = COLOR::BLACK;
			computer = COLOR::WHITE;
			return;
		}
		else
		{
			std::cout << "Invalid input, please try again" << std::endl;
		}
	}
}

void HexBoard::printBoard()
{
	int rowNum(0);
	std::string emptySpace("");
	for (std::vector<Node> row : m_board)
	{
		// Print spacing between rows
		if (rowNum)
		{
			// Print initial spacers
			emptySpace += " ";
			std::cout << emptySpace;

			// Print spacing ascii values
			for (int i = 1; i < m_size; i++)
			{
				std::cout << "\\ / ";
			}
			std::cout << "\\" << std::endl;
		}

		// Print initial spacers
		emptySpace += " ";
		std::cout << emptySpace;
		bool first(true);
		//Print column spacing
		for (Node node : row)
		{
			if (!first) {
				std::cout << " - ";
			}
			first = false;
			std::cout << node;
		}
		std::cout << std::endl;

		rowNum++;
	}

	return;
}
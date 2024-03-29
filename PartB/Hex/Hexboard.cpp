#include "HexBoard.h"
#include <ctime>
#include <random>

HexBoard::HexBoard(int size) : m_turns(0), m_size(size), m_player(COLOR::NONE), m_computer(COLOR::NONE)
{
	m_algo = GraphAlgos();
	m_board_state = std::vector<std::vector<COLOR>>(m_size, std::vector<COLOR>(m_size, COLOR::NONE));

	for (int i = 0; i < m_size; i++)
	{
		m_board.emplace_back(std::vector<Node*>());
		for (int j = 0; j < m_size; j++)
		{
			Node* new_node = new Node();
			new_node->addRow(i);
			new_node->addCol(i);
			m_board[i].emplace_back(new_node);
		}
	}

	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			//Node* node = m_board[i][j];
			std::vector<Node*> node_neighbors;

			// Corners
			if (i == 0 && j == 0)
			{
				//top left corner
				node_neighbors.push_back(m_board[i][j + 1]);
				node_neighbors.push_back(m_board[i+1][j]);
			}
			else if (i == m_size-1 && j == 0)
			{
				// bottom left corner
				node_neighbors.push_back(m_board[i-1][j]);
				node_neighbors.push_back(m_board[i][j+1]);
			}
			else if (i == 0 && j == m_size-1)
			{
				// top right corner
				node_neighbors.push_back(m_board[i][j-1]);
				node_neighbors.push_back(m_board[i+1][j]);
				node_neighbors.push_back(m_board[i+1][j-1]);
			}
			else if (i == m_size-1 && j == m_size-1)
			{
				// bottom right corner
				node_neighbors.push_back(m_board[i][j-1]);
				node_neighbors.push_back(m_board[i-1][j]);
				node_neighbors.push_back(m_board[i-1][j-1]);
			}
			// Edges
			else if (i == 0)
			{
				// Top row
				node_neighbors.push_back(m_board[i][j-1]);
				node_neighbors.push_back(m_board[i][j+1]);
				node_neighbors.push_back(m_board[i+1][j-1]);
				node_neighbors.push_back(m_board[i+1][j]);
			}
			else if (i == m_size-1)
			{
				// Bottom Row
				node_neighbors.push_back(m_board[i][j-1]);
				node_neighbors.push_back(m_board[i][j+1]);
				node_neighbors.push_back(m_board[i-1][j]);
				node_neighbors.push_back(m_board[i-1][j+1]);
			}
			else if (j == 0)
			{
				// Left Column
				node_neighbors.push_back(m_board[i-1][j]);
				node_neighbors.push_back(m_board[i+1][j]);
				node_neighbors.push_back(m_board[i-1][j+1]);
				node_neighbors.push_back(m_board[i][j+1]);
			}
			else if (j == m_size-1)
			{
				// Right Column
				node_neighbors.push_back(m_board[i-1][j]);
				node_neighbors.push_back(m_board[i+1][j]);
				node_neighbors.push_back(m_board[i][j-1]);
				node_neighbors.push_back(m_board[i+1][j-1]);
			}
			// Central node
			else
			{
				node_neighbors.push_back(m_board[i][j-1]);
				node_neighbors.push_back(m_board[i][j+1]);
				node_neighbors.push_back(m_board[i-1][j]);
				node_neighbors.push_back(m_board[i+1][j]);
				node_neighbors.push_back(m_board[i-1][j+1]);
				node_neighbors.push_back(m_board[i+1][j-1]);
			}
			m_board[i][j]->addNeighbor(node_neighbors);
		}
	}
}

HexBoard::~HexBoard() 
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			delete m_board[i][j];
		}
	}
}

void HexBoard::startGame()
{
	playerSetup();

	bool end(false);
	COLOR turn = COLOR::WHITE;
	COLOR winner = COLOR::NONE;
	while (winner == COLOR::NONE)
	{
		makeMove(turn);
		turn == COLOR::WHITE ? turn = COLOR::BLACK : turn = COLOR::WHITE;
		winner = checkForWinner();
	}
	
	if (winner == COLOR::WHITE)
	{
		std::cout << "White wins!" << std::endl;
	}
	else
	{
		std::cout << "Black wins!" << std::endl;
	}
}

void HexBoard::makeMove(COLOR player)
{
	int row, column;
	
	while (true)
	{
		if (player == m_player)
		{
			// Player select move
			std::cout << "Enter Row and Column of next move (0-" << m_size - 1 << ")" << std::endl;
			std::cin >> row;
			std::cin >> column;
		}
		else
		{
			// Computer select move
			pair<int, int> next_move = runMC(1000);
			row = next_move.first;
			column = next_move.second;
		}

		if (0 <= row && row < m_size && 0 <= column && column < m_size)
		{
			Node* target = m_board[row][column];
			if (target->getColor() == COLOR::NONE)
			{
				m_board[row][column]->setColor(player);
				m_board_state[row][column] = player;
				printBoard();
				m_turns++;
				return;
			}
		}
		if (player == m_player)
		{
			std::cout << "Invalid Move: select another move" << std::endl;
		}
	}
}

pair<int, int> HexBoard::runMC(int numTrials)
{
	// Structure to store location of winning moves
	std::vector<std::vector<int>> m_winning_trials(m_size, std::vector<int>(m_size, 0));

	// List of pieces left to play
	int turns_left = pow(m_size, 2) - m_turns;
	std::vector<COLOR> moves(turns_left, m_computer); 

	// Integer auto "rounds" down on odd turns giving m_computer one more move
	std::fill(moves.begin(), moves.begin() + turns_left/2, m_player); 

	for(int iii = 0; iii < numTrials; iii++)
	{
		std::shuffle(moves.begin(), moves.end(), std::default_random_engine(time(0)));
		
		int moves_index = 0;
		// Fill rest of board randomly
		for (int i = 0; i < m_size; i++)
		{
			for (int j = 0; j < m_size; j++)
			{
				if (m_board_state[i][j] == COLOR::NONE)
				{
					m_board[i][j]->setColor(moves[moves_index]);
					moves_index++;
				}
			}
		}

		// Did MC trial win?
		bool winning_pos(checkForWinner(true) == m_computer);

		for (int i = 0; i < m_size; i++)
		{
			for (int j = 0; j < m_size; j++)
			{
				// Increase value of winning moves
				if (winning_pos && m_board_state[i][j] == COLOR::NONE && m_board[i][j]->getColor() == m_computer)
				{
					m_winning_trials[i][j]++;
				}

				// Reset to current game state
				m_board[i][j]->setColor(m_board_state[i][j]);
			}
		}
	}

	// Return best row/column move
	int max = 0;
	pair<int, int> ans;
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			if (m_winning_trials[i][j] > max)
			{
				max = m_winning_trials[i][j];
				ans.first = i;
				ans.second = j;
			}
		}
	}

	return ans;
}

// Have user choose to go first or second
void HexBoard::playerSetup()
{
	while (true)
	{
		std::cout << "Choose a color: Enter 'w' for White (goes first) or 'b' for Black (goes second)" << std::endl;
		std::string input;
		std::cin >> input;

		if (input.compare("w") == 0)
		{
			m_player = COLOR::WHITE;
			m_computer = COLOR::BLACK;
			printBoard();
			std::cout << "You chose white! Make a full path from left to right" << std::endl;
			return;
		}
		else if (input.compare("b") == 0)
		{
			m_player = COLOR::BLACK;
			m_computer = COLOR::WHITE;
			printBoard();
			std::cout << "You chose black! Make a full path from top to bottom" << std::endl;
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
	for (std::vector<Node*> row : m_board)
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
		for (Node* node : row)
		{
			if (!first) {
				std::cout << " - ";
			}
			first = false;
			std::cout << *node;
		}
		std::cout << std::endl;

		rowNum++;
	}

	return;
}

COLOR HexBoard::checkForWinner(bool fullBoard)
{
	std::vector<Node*> start_edge_w, start_edge_b, end_edge_w, end_edge_b;

	for (int i = 0; i < m_size; i++)
	{
		start_edge_w.push_back(m_board[i][0]);
		end_edge_w.push_back(m_board[i][m_size - 1]);

		start_edge_b.push_back(m_board[0][i]);
		end_edge_b.push_back(m_board[m_size - 1][i]);
	}
	
	for (auto node : start_edge_w)
	{
		pair<deque<Node*>, int> path = m_algo.findPath(node, end_edge_w, COLOR::WHITE);
		if (path.second != std::numeric_limits<int>::max())
		{
			return COLOR::WHITE;
		}
	}

	if (fullBoard)
	{
		// if full board and has not return white yet, then black won.
		return COLOR::BLACK;
	}

	for (auto node: start_edge_b)
	{
		pair<deque<Node*>, int> path = m_algo.findPath(node, end_edge_b, COLOR::BLACK);
		if (path.second != std::numeric_limits<int>::max())
		{
			return COLOR::BLACK;
		}
	}
	return COLOR::NONE;
}
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const int height = 10;
const int width = 10;



#define obf_block_start
void ShowBoard(unsigned char** board)
{

	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{
			std::cout << board[i][j] << " ";
		}
		std::cout << "|" << i;
		std::cout << std::endl;
	}
	for (int j = 0; j < width; j++)
	{
		std::cout << "__";
	}
	std::cout << "|" << std::endl;

	for (int j = 0; j < width; j++)
	{
		std::cout << j << " ";
	}
	std::cout << std::endl;
}
#define obf_block_end

enum SaperSign { bombSign = '*', fog = '@', flagged = '#', space = ' ', exposed = 'E' };

int CheckBombs(unsigned char** board, int x, int y)
{
	int bombs = 0;

	if (x - 1 >= 0)
	{
		if (board[x - 1][y] == bombSign)
		{
			bombs = bombs + 1;
		}
		if (y - 1 >= 0)
		{
			if (board[x - 1][y - 1] == bombSign)
			{
				bombs = bombs + 1;
			}
		}
		if (y + 1 < width)
		{
			if (board[x - 1][y + 1] == bombSign)
			{
				bombs = bombs + 1;
			}
		}
	}

	if (y - 1 >= 0)
	{
		if (board[x][y - 1] == bombSign)
		{
			bombs = bombs + 1;
		}
	}

	if (y + 1 < width)
	{
		if (board[x][y + 1] == bombSign)
		{
			bombs = bombs + 1;
		}
	}

	if (x + 1 < height)
	{
		if (board[x + 1][y] == bombSign)
		{
			bombs = bombs + 1;
		}
		if (y - 1 >= 0)
		{
			if (board[x + 1][y - 1] == bombSign)
			{
				bombs = bombs + 1;
			}
		}
		if (y + 1 < width)
		{
			if (board[x + 1][y + 1] == bombSign)
			{
				bombs = bombs + 1;
			}
		}
	}


	return bombs;
}


bool ExposeNullFieldHelp(unsigned char** board, unsigned char** boardFog, int x, int y)
{
	int temp = CheckBombs(board, x, y);
	if (board[x][y] != exposed)
	{
		if (temp == 0)
		{
			boardFog[x][y] = space;
			board[x][y] = exposed;
			return true;
		}
		else
		{
			boardFog[x][y] = temp + '0';
			board[x][y] = exposed;
			return false;
		}
	}
	return false;
}

void ExposeNullFields(unsigned char** board, unsigned char** boardFog, int x, int y)
{

	if (x - 1 >= 0)
	{
		if (ExposeNullFieldHelp(board, boardFog, x - 1, y) == true)
		{
			ExposeNullFields(board, boardFog, x - 1, y);
		}

		if (y - 1 >= 0)
		{
			if (ExposeNullFieldHelp(board, boardFog, x - 1, y - 1) == true)
			{
				ExposeNullFields(board, boardFog, x - 1, y - 1);
			}
		}

		if (y + 1 < width)
		{

			if (ExposeNullFieldHelp(board, boardFog, x - 1, y + 1) == true)
			{
				ExposeNullFields(board, boardFog, x - 1, y + 1);
			}

		}

	}

	if (y - 1 >= 0)
	{
		if (ExposeNullFieldHelp(board, boardFog, x, y - 1) == true)
		{
			ExposeNullFields(board, boardFog, x, y - 1);
		}
	}


	if (y + 1 < width)
	{
		if (ExposeNullFieldHelp(board, boardFog, x, y + 1) == true)
		{
			ExposeNullFields(board, boardFog, x, y + 1);
		}
	}

	if (x + 1 < height)
	{

		if (ExposeNullFieldHelp(board, boardFog, x + 1, y) == true)
		{
			ExposeNullFields(board, boardFog, x + 1, y);
		}
		if (y - 1 >= 0)
		{

			if (ExposeNullFieldHelp(board, boardFog, x + 1, y - 1) == true)
			{
				ExposeNullFields(board, boardFog, x + 1, y - 1);
			}
		}
		if (y + 1 < width)
		{

			if (ExposeNullFieldHelp(board, boardFog, x + 1, y + 1) == true)
			{
				ExposeNullFields(board, boardFog, x + 1, y + 1);
			}
		}

	}


}

bool MakeMove(unsigned char** board, unsigned char** boardFog, int x, int y, int mode)
{
	if (mode == 2)
	{
		if (boardFog[x][y] == fog)
		{
			boardFog[x][y] = flagged;
		}
		else if (boardFog[x][y] == flagged)
		{
			boardFog[x][y] = fog;
		}
		else
		{
			std::cout << "This field is exposed!" << std::endl;
		}

		return false;
	}

	if (boardFog[x][y] != fog)
	{
		std::cout << "Wrong move!" << std::endl;
		return false;
	}

	if (board[x][y] == bombSign)
	{
		std::cout << "You lost!" << std::endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (board[i][j] == bombSign)
				{
					boardFog[i][j] = bombSign;
				}
			}
		}

		return true;
	}

	int bombs = CheckBombs(board, x, y);

	if (bombs == 0)
	{
		boardFog[x][y] = space;
		board[x][y] = exposed;
		ExposeNullFields(board, boardFog, x, y);
	}
	else
	{
		boardFog[x][y] = bombs + 48;
		board[x][y] = exposed;
	}

	return false;


}

bool isWin(unsigned char** board, unsigned char** boardFog, std::vector<std::pair<int, int>> bombsIndex, int bombs)
{
	std::vector<int> v_flaggedBombs;
	for (int i = 0; i < bombsIndex.size(); i++)
	{
		v_flaggedBombs.push_back(i);
	}
	int flaggedBombs = 0;
	int element = 0;
	for (auto bombIndex : bombsIndex)
	{
		if (boardFog[bombIndex.first][bombIndex.second] == space && board[bombIndex.first][bombIndex.second] == bombSign)
		{
			flaggedBombs++;
			v_flaggedBombs.erase(v_flaggedBombs.begin() + element);
			element++;
		}
	}

	if (flaggedBombs == bombs)
	{
		std::cout << "You won!" << std::endl;
		return true;
	}

	int x = 0;
	int y = 0;
	bool isAllClear = true;
	for (int v_element : v_flaggedBombs)
	{
		x = bombsIndex[v_element].first;
		y = bombsIndex[v_element].second;

		if (x - 1 >= 0)
		{
			if (board[x - 1][y] != exposed && board[x - 1][y] != bombSign)
			{
				return false;
			}
			if (y - 1 >= 0)
			{
				if (board[x - 1][y - 1] != exposed && board[x - 1][y - 1] != bombSign)
				{
					return false;
				}
			}
			if (y + 1 < width)
			{
				if (board[x - 1][y + 1] != exposed && board[x - 1][y + 1] != bombSign)
				{
					return false;
				}
			}
		}


		if (y - 1 >= 0)
		{
			if (board[x][y - 1] != exposed && board[x][y - 1] != bombSign)
			{
				return false;
			}
		}

		if (y + 1 < width)
		{
			if (board[x][y + 1] != exposed && board[x][y + 1] != bombSign)
			{
				return false;
			}
		}

		if (x + 1 < height)
		{
			if (board[x + 1][y] != exposed && board[x + 1][y] != bombSign)
			{
				return false;
			}
			if (y - 1 >= 0)
			{
				if (board[x + 1][y - 1] != exposed && board[x + 1][y - 1] != bombSign)
				{
					return false;
				}
			}
			if (y + 1 < width)
			{
				if (board[x + 1][y + 1] != exposed && board[x + 1][y + 1] != bombSign)
				{
					return false;
				}
			}
		}
	}

	if (isAllClear == true)
	{
		for (auto bomb : bombsIndex)
		{
			if (boardFog[bomb.first][bomb.second] == fog)
			{
				boardFog[bomb.first][bomb.second] = flagged;
			}
		}
		std::cout << "You won!" << std::endl;
		return true;
	}

	return false;
}

int ReturnMove(int limiter, std::string information, int minimum = 0)
{
	int input = -1;


rewindTime:
	std::cout << information;
	std::cin >> input;
	while (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Bad input! Try again" << std::endl;
		std::cout << information;
		std::cin >> input;
	}

	if (input < minimum || input >= limiter)
	{

		std::cout << "Bad input! Try again" << std::endl;
		goto rewindTime;
	}


	return input;
}


int main()
{
	int bombs = 0;

	unsigned char** board = new unsigned char* [height];
	unsigned char** boardFog = new unsigned char* [height];
	for (int i = 0; i < height; i++)
	{
		board[i] = new unsigned char[width];
		boardFog[i] = new unsigned char[width];
		for (int j = 0; j < width; j++)
		{
			board[i][j] = '0';
			boardFog[i][j] = fog;
		}
	}


	ShowBoard(boardFog);


	std::vector<int> bombsPositions;
	std::vector<std::pair<int, int>> bombsIndex;


	std::ifstream bombsPosition("bombs.txt");
	if (!bombsPosition)
	{
		std::cout << "Can't open the file!" << std::endl;
		return 0;
	}



	std::string position = "";
	while (std::getline(bombsPosition, position, ','))
	{
		unsigned char _char = atoi(position.c_str());
		bombsPositions.push_back(_char);
		if (_char == bombSign)
		{
			bombs++;
		}
	}


	int k = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j] = bombsPositions[k++];
			if (board[i][j] == bombSign)
			{
				bombsIndex.push_back(std::pair<int, int>(i, j));
			}
		}
	}

	std::cout << std::endl;
	ShowBoard(boardFog);

	bool isEnd = false;
	int x = 0;
	int y = 0;
	int mode = 0;
	do
	{
		//std::cout << "Debug Mode2" << std::endl;

		mode = ReturnMove(3, "Expose(1) or Flag(2)? = ", 1);

		x = ReturnMove(height, "X = ");
		y = ReturnMove(width, "Y = ");

		isEnd = MakeMove(board, boardFog, x, y, mode);
		if (isEnd == false)
		{
			isEnd = isWin(board, boardFog, bombsIndex, bombs);
		}
		ShowBoard(boardFog);


	} while (isEnd == false);


	for (int i = 0; i < height; i++)
	{
		delete[] boardFog[i];
		delete[] board[i];
	}
	delete[] board;
	delete[] boardFog;

	return 0;
}
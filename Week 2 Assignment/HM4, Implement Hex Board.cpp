#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <ctime>

using namespace std;

enum class player { BLUE, RED };

class BoardGraph
{
public:
	BoardGraph() {}
	BoardGraph(int size):
		size(size), board(size, vector<char>(size, '.'))
	{
		edges = "\\";
		for (int i=1; i<size; i++)
		{
			edges += " / \\";
		}
	}

	// make a move and if it's legal, return true
	bool makeMove(int x, int y, player p);

	// undo a false move
	bool undo(int x, int y);

	// see if a player won or not
	bool win(int x, int y);

	// print the board
	void printBoardGraph();

private:
	bool ValidMove(int x, int y);
	void checkBorders(int x, int y,
			vector<bool> &flags, char side);

	const static int directions[6][2]; // six directions
	const static char Blue = 'B';
	const static char Red = 'R';
	const static char Blank = '.';
	int size;
	string edges;
	vector<vector<char> > board;
};

void BoardGraph::printBoardGraph()
{
	// first line
	cout << board[0][0];
	for (int j=1; j<size; j++)
		cout << " - " << board[0][j];
	cout << endl;

	string space = "";
	for (int i=1; i<size; i++)
	{
		space += ' ';
		cout << space << edges << endl;
		space += ' ';
		cout << space << board[i][0];
		for (int j=1; j<size; j++)
			cout << " - " << board[i][j];
		cout << endl;
	}
}

bool BoardGraph::ValidMove(int x, int y)
{
	return x>=0 && x<size && y>=0 && y<size;
}

void BoardGraph::checkBorders(int x, int y,
		vector<bool> &flags, char side)
{
	if (side == Blue)
	{
		if (y == 0)
			flags[0] = true;
		if (y == size - 1)
			flags[1] = true;
	}
	else if (side == Red)
	{
		if (x == 0)
			flags[0] = true;
		if (x == size - 1)
			flags[1] = true;
	}
}

const int BoardGraph::directions[6][2] =
{
	{-1, 0}, {-1, 1}, // top left, top right
	{0, -1}, {0, 1},  // left, right
	{1, -1}, {1, 0}   // buttom left, buttom right
};

bool BoardGraph::makeMove(int x, int y , player p)
{
	if (ValidMove(x, y) == false)
		return false;

	if (board[x][y] != Blank)
		return false;

	if (p == player::BLUE)
		board[x][y] = Blue;
	else if (p == player::RED)
		board[x][y] = Red;

	return true;
}

bool BoardGraph::undo(int x, int y)
{
	if (ValidMove(x, y) == false)
		return false;

	board[x][y] = Blank;

	return true;
}

bool BoardGraph::win(int x, int y)
{
	if (ValidMove(x, y) == false || board[x][y] == Blank)
		return false;

	char side = board[x][y];
	vector<bool> flags(2, false);

	vector<vector<bool> > visited(size, vector<bool>(size));
	queue<pair<int, int> > traces;
	traces.push(make_pair(x, y));
	visited[x][y] = true;

	while (!traces.empty())
	{
		auto top = traces.front();
		checkBorders(top.first, top.second, flags, side);
		traces.pop();

		for (int n=0; n<6; n++)
		{
			int curX = top.first + directions[n][0];
			int curY = top.second + directions[n][1];
			if (ValidMove(curX, curY) && board[curX][curY] == side
					&& visited[curX][curY] == false)
			{
				visited[curX][curY] = true;
				traces.push(make_pair(curX, curY));
			}
		}
	}

	return flags[0] && flags[1];
}

int main()
{
	const int SIZE = 11;
	BoardGraph board(SIZE);
	cout << "Initialize Hex board" << endl;
	board.printBoardGraph();

	int turn = 0;
	int steps = 0;
	int x, y;
	srand(time(0));
	while (true)
	{
		steps++;
		turn = !turn;
		if (turn == 1)
		{
			do
			{
				x = rand() % SIZE;
				y = rand() % SIZE;
			}while (!board.makeMove(x, y, player::BLUE));

			cout << "Player Blue: (" << x << "," << y << ")" << endl;
		}
		else
		{
			do
			{
				x = rand() % SIZE;
				y = rand() % SIZE;
			}while (!board.makeMove(x, y, player::RED));

			cout << "Player Red: (" << x << "," << y << ")" << endl;
		}

		if (board.win(x, y))
		{
			cout << (turn ? "Blue" : "Red") << " win" << endl;
			cout << "Total steps = " << steps << endl;
			board.printBoardGraph();
			break;
		}
	}

	return 0;
}

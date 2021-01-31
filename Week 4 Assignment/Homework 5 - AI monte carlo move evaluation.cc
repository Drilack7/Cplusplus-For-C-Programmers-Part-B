//This program lets the user play the game of hex with
//the computer as opponent. The computer uses AI to play
//the game the right way. Each player's move should have
//the following form: i,j. Write the two number in the
//same line with a comma in between. The computer seems
//to play very smart and is unbeatable in a size 5 board.
//Enjoy.
//Christos Drilakis, 23/01/2021.

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <ctime>
#include <iterator>
#include <algorithm>

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

	//make a move and if it's legal, return true
	bool makeMove(int x, int y, player p);

	//undo a false move
	bool undo(int x, int y);

	//see if a player won or not
	bool win(int x, int y);

	//print the board
	void printBoardGraph();

	//compute the best move with AI
	pair<int,int> AIalgorithm();

	//copy constructor
	BoardGraph(const BoardGraph &board2)
	{
	    board = board2.board;
	    edges = board2.edges;
	    size = board2.size;
	}

private:
	bool ValidMove(int x, int y);
	void checkBorders(int x, int y,
			vector<bool> &flags, char side);

	const static int directions[6][2]; //six directions
	const static char Blue = 'X'; //blue is the first player
	const static char Red = 'O';
	const static char Blank = '.';
	int size;
	string edges;
	vector<vector<char> > board;
};

void BoardGraph::printBoardGraph()
{
	//first line
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
	return x>=0 && x<size && y>=0 && y<size && board[x][y] == Blank;
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
	{-1, 0}, {-1, 1}, //top left, top right
	{0, -1}, {0, 1},  //left, right
	{1, -1}, {1, 0}   //buttom left, buttom right
};

bool BoardGraph::makeMove(int x, int y , player p)
{
	if (ValidMove(x, y) == false)
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
			if (curX>=0 && curX<size && curY>=0 && curY<size &&
                board[curX][curY] == side && visited[curX][curY] == false)
			{
				visited[curX][curY] = true;
				traces.push(make_pair(curX, curY));
			}
		}
	}

	return flags[0] && flags[1];
}

pair<int,int> BoardGraph::AIalgorithm()
{
    //vectors for shuffling and counting the empty spots
    vector<int> emptySpots, emptySpotsCounter(size*size);

    for (int x=0; x<size; ++x)
        for (int y=0; y<size; ++y)
            if(board[x][y]==Blank)
            {
                emptySpots.push_back(x*size+y); //vector with all remaining empty spots
                ++emptySpotsCounter[x*size+y]; //all the empty spots take value 1
            }

    vector<int> emptySpotsCopy = emptySpots; //copy vector for initialization

    int wins=0, turn = 0, lastElement;
    vector<int> bestMoves(size*size); //stores all the best moves

    vector<vector<char>> testboard = board; //copy of hex board for initialization

    for(int trials=0; trials<10000; ++trials)
    {
        board = testboard;
        emptySpots = emptySpotsCopy;
        random_shuffle(emptySpots.begin(), emptySpots.end());
        while (emptySpots.size()) //fill up the remaining empty spots on the board
        {
            lastElement = emptySpots[emptySpots.size()-1];
            turn = !turn;
            if (turn == 1)
            {
                makeMove(lastElement/size, lastElement%size, player::BLUE);
                emptySpots.pop_back();
            }
            else
            {
                makeMove(lastElement/size, lastElement%size, player::RED);
                emptySpots.pop_back();
            }
        }

        for (int x=0; x<size; ++x)
        {
            for (int y=0; y<size; ++y)
            {
                if(board[x][y]==Blue && win(x,y) && emptySpotsCounter[x*size+y]==1)
                {
                    ++bestMoves[x*size+y]; //store all the moves that led to a win
                    ++wins;
                }
            }
        }
    }

    vector<int>::iterator maxElement; //iterator to find the move with the best chances to win
    maxElement = max_element(bestMoves.begin(), bestMoves.end()); //max value means best move

    int dist = distance(bestMoves.begin(), maxElement); //position of max value
    //transpose into 2d coordinates
    int row = dist/size;
    int col = dist%size;

    if (*maxElement==0) //in case there is no winning choice
    {
        row = emptySpotsCopy[0]/size;
        col = emptySpotsCopy[0]%size;
    }

    return make_pair(row, col);
}

int main()
{
	const int SIZE = 5;
	BoardGraph board1(SIZE); //create the board to play

	int turn = 0;
	int steps = 0;
	int x, y;
	char comma;
	srand(time(0));

	pair<int,int> AImove; //the move that AI decides to play

	while (true)
	{
		steps++;
		turn = !turn;
		if (turn == 1)
		{
			BoardGraph board2 = board1; //copy of the board for testing the best play
			AImove = board2.AIalgorithm(); //the AI method outputs a pair of ints
			x = AImove.first;
			y = AImove.second;
			board1.makeMove(x, y, player::BLUE); //
			cout << "Computer: (" << x << "," << y << ")" << endl;
			board1.printBoardGraph();
		}
		else
		{
			while (true)
            {
                cout << "Input coordinates (write \"x,y\" and then press enter): ";
                cin >> x >> comma >> y;
                if (board1.makeMove(x, y, player::RED)==true)
                    break;
                else
                    cout << "Invalid values! Try again!\n";
            }

			cout << "Human: (" << x << "," << y << ")" << endl;
		}

		if (board1.win(x, y))
		{
			if (turn==0)
                board1.printBoardGraph();
			cout << (turn ? "Computer" : "Human") << " wins!" << endl;
			cout << "Total steps = " << steps << endl;
			break;
		}
	}

	return 0;
}

#include"Board.h"
#include"Random.h"
#include<fstream>
using namespace std;

// Gives values to rows + columns + mines
void Board::LoadConfiguration()
{
	ifstream inFile("boards/config.cfg");
	string temp;

	if (inFile.is_open())
	{
		inFile >> this->columns;
		inFile >> this->rows;
		inFile >> this->mines;

	}

	int numTiles = rows * columns;

	inFile.close();
}

void Board::SetMinesRandom()
{
	int tempNumMines = 0;

	LoadConfiguration();

	while (tempNumMines < mines)
	{
		int x = Random::Int(0, (tiles.size() - 1));

		if (tiles[x].hasMine == false)
		{
			tiles[x].hasMine = true;
			tempNumMines++;
		}

	}
}

void Board::LoadBoardFromFile(string fileName)
{

	ifstream file(fileName);
	string fullBoard;
	string temp;
	int tempColumn = 0;

	if (file.is_open())
	{
		while (getline(file, temp))
		{
			fullBoard += temp;
		}
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		if (fullBoard[i] == '1')
		{
			tiles[i].hasMine = 1;
			mines++;
		}			
		else
			tiles[i].hasMine = 0;
	}

	/*
	for (int i = 0; i < tiles.size(); i++)
	{
		cout << tiles[i].hasMine << endl;
	}
	*/
}

Board::Board()
{
	LoadConfiguration();

	for (int i = 0; i < (rows * columns); i++)
	{
		Tile tile;

		tile.isFlagged = 0;
		tile.isRevealed = 0;
		tile.hasMine = 0;

		tiles.push_back(tile);
	}

	SetMinesRandom();

	SetAdjacentTiles();

	/*
	for (int i = 0; i < tiles.size(); i++)
	{
		cout << tiles[i].isRevealed << " " << tiles[i].isFlagged << " " << tiles[i].hasMine << endl;
	}
	*/
}

// Adjacent tiles need to be set + Number value for each tile needs to be set
Board::Board(string fileName)
{
	LoadConfiguration();

	mines = 0;

	for (int i = 0; i < (rows * columns); i++)
	{
		Tile tile;
		tile.isFlagged = 0;
		tile.isRevealed = 0;
		tile.hasMine = 0;

		tiles.push_back(tile);

	}

	LoadBoardFromFile(fileName);

	SetAdjacentTiles();

	/*
	for (int i = 0; i < tiles.size(); i++)
	{
		cout << tiles[i].isRevealed << " " << tiles[i].isFlagged << " " << tiles[i].hasMine << endl;
	}
	*/
}

void Board::LoadNewBoard(string board)
{
	Clear();

	if (board == "random")
	{
		SetMinesRandom();
		SetAdjacentTiles();
	}

	if (board == "test1")
	{
		mines = 0;

		LoadBoardFromFile("boards/testboard1.brd");
		SetAdjacentTiles();
	}

	if (board == "test2")
	{
		mines = 0;

		LoadBoardFromFile("boards/testboard2.brd");
		SetAdjacentTiles();
	}

	if (board == "test3")
	{
		mines = 0;

		LoadBoardFromFile("boards/testboard3.brd");
		SetAdjacentTiles();
	}
}

// Does not change mine value
void Board::Clear()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].isRevealed = 0;
		tiles[i].hasMine = 0;
		tiles[i].isFlagged = 0;

		tiles[i].numberOnTile = 0;
	}

}

// Sets up the vector<Tile*> for each Tile that is being pushed into the tiles vector
void Board::SetAdjacentTiles()
{
	int x = 0;
	int y = 0;

	for (int i = 0; i < tiles.size(); i++)
	{
		x = i % columns; // Rows
		y = i / columns; // Columns

		vector<Tile*> tilePointers;

		// The top-left Tile
		if (x == 0 && y == 0)
		{
			tilePointers.push_back(&tiles[i + 1]);
			tilePointers.push_back(&tiles[i + columns]);
			tilePointers.push_back(&tiles[i + columns + 1]);
		}

		// The top-right TIle
		else if (y == 0 && x == columns - 1)
		{
			tilePointers.push_back(&tiles[i - 1]);
			tilePointers.push_back(&tiles[i + columns - 1]);
			tilePointers.push_back(&tiles[i + columns]);
		}

		// The bottom-right Tile
		else if (x == columns - 1 && y == rows - 1)
		{
			tilePointers.push_back(&tiles[i - 1]);
			tilePointers.push_back(&tiles[i - columns - 1]);
			tilePointers.push_back(&tiles[i - columns]);
		}

		// The bottom-left Tile
		else if (x == 0 && y == rows - 1)
		{
			tilePointers.push_back(&tiles[i + 1]);
			tilePointers.push_back(&tiles[i - columns + 1]);
			tilePointers.push_back(&tiles[i - columns]);
		}

		// The Tiles in the first row
		else if (y == 0)
		{
			tilePointers.push_back(&tiles[i - 1]);
			tilePointers.push_back(&tiles[i + 1]);
			tilePointers.push_back(&tiles[i + columns - 1]);
			tilePointers.push_back(&tiles[i + columns]);
			tilePointers.push_back(&tiles[i + columns + 1]);
		}

		// The tiles in the last column
		else if (x == columns - 1)
		{
			tilePointers.push_back(&tiles[i - columns - 1]);
			tilePointers.push_back(&tiles[i - columns]);
			tilePointers.push_back(&tiles[i - 1]);
			tilePointers.push_back(&tiles[i + columns - 1]);
			tilePointers.push_back(&tiles[i + columns]);
		}



		// The tiles in the last row
		else if (y == rows - 1)
		{
			tilePointers.push_back(&tiles[i - 1]);
			tilePointers.push_back(&tiles[i + 1]);
			tilePointers.push_back(&tiles[i - columns]);
			tilePointers.push_back(&tiles[i - columns - 1]);
			tilePointers.push_back(&tiles[i - columns + 1]);
		}



		// The tiles in the first column
		else if (x == 0)
		{
			tilePointers.push_back(&tiles[i + columns + 1]);
			tilePointers.push_back(&tiles[i + 1]);
			tilePointers.push_back(&tiles[i + columns]);
			tilePointers.push_back(&tiles[i - columns]);
			tilePointers.push_back(&tiles[i - columns + 1]);
		}

		// All the remaining tiles
		else
		{
			tilePointers.push_back(&tiles[i - 1]);
			tilePointers.push_back(&tiles[i + 1]);
			tilePointers.push_back(&tiles[i + columns]);
			tilePointers.push_back(&tiles[i - columns]);
			tilePointers.push_back(&tiles[i - columns + 1]);
			tilePointers.push_back(&tiles[i + columns + 1]);
			tilePointers.push_back(&tiles[i - columns - 1]);
			tilePointers.push_back(&tiles[i + columns - 1]);

		}

		tiles[i].adjacentTiles = tilePointers;

		tiles[i].FindNumberOnTile();
	}
}

void Board::OpenEmptyTileRecursive(Tile& tile)
{
	if (tile.isFlagged == 1 || tile.hasMine == 1)
		return;
	if (tile.numberOnTile != 0)
		return;

	if (tile.numberOnTile == 0)
	{
		for (int i = 0; i < tile.adjacentTiles.size(); i++)
		{
			tile.adjacentTiles[i]->isRevealed = true;
			OpenEmptyTileRecursive(*tile.adjacentTiles[i]);
		}
	}
	
}
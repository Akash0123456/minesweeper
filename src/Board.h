#pragma once
#include"Tile.h"
#include<vector>
#include<string>
using namespace std;

struct Board
{
	int mines;

	int rows;
	int columns;

	int numTiles;

	vector<Tile> tiles;

	Board();

	Board(string filename);

	void LoadBoardFromFile(string fileName);

	void LoadConfiguration();
	void SetMinesRandom();

	void Clear();
	void LoadNewBoard(string board);

	void SetAdjacentTiles();

	void OpenEmptyTileRecursive(Tile& tile);

};	
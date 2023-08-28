#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
using namespace std;

struct Tile
{
	bool isRevealed;
	bool hasMine;
	bool isFlagged;

	int numberOnTile;

	vector <Tile*> adjacentTiles;

	int xPosition;
	int yPosition;

	Tile();

	void FindNumberOnTile();
};

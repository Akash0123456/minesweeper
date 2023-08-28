#include"Tile.h"

Tile::Tile()
{
	isRevealed = false;
	hasMine = false;
	isFlagged = false;

	numberOnTile = 0;

	xPosition = 0;
	yPosition = 0;

}

void Tile::FindNumberOnTile()
{
	for (int i = 0; i < adjacentTiles.size(); i++)
	{
		if (adjacentTiles[i]->hasMine == 1)
			numberOnTile++;

	}
}
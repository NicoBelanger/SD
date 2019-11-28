#include "map.h"

map::map()
{
}

void map::createObstacle(int p_x, int p_y)
{
	tiles[p_x][p_y].obstacle = true;
}

void map::createObstacle(int x_from, int y_from, int x_to, int y_to)
{
	for (int i = x_from; i <= x_to; i++)
	{
		for (int j = y_from; j<= y_to; j++)
		{
			tiles[i][j].obstacle = true;
		}
	}
}

void map::setTile(node p_tile)
{
	tiles[p_tile.x][p_tile.y] = p_tile;
}

#pragma once
#include "node.h"

class map
{
	public:
		static const int x = 50;
		static const int y = 50;

		 node tiles[x][y];

		map();
		void createObstacle(int p_x, int p_y);
		void createObstacle(int x_from, int y_from, int x_to, int y_to);
		void setTile(node p_tile);
};


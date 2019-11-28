#include "node.h"

bool operator<(const node& lhs, const node& rhs)
{
	return lhs.fCost < rhs.fCost;
}

node::node()
{
	obstacle = false;
}

node::node(int p_x, int p_y)
{
	x = p_x;
	y = p_y;
	obstacle = false;
}

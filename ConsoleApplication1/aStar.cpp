#include "aStar.h"

aStar::aStar()
{
}

bool aStar::isValid(int x, int y)
{
	int id = x + y * (map::x);
	if (id == 0) {
		if (x < 0 || y < 0 || x >= (map::x) || y >= (map::y)) {
			return false;
		}
		return true;
	}
	return false;
}

bool aStar::isValid(node p_node)
{
	if (p_node.obstacle == false) {
		if (p_node.x < 0 || p_node.y < 0 || p_node.x >= (map::x) || p_node.y >= (map::y)) {
			return false;
		}
		return true;
	}
	return false;
}

bool aStar::isDestination(int x, int y, node dest)
{
	if (x == dest.x && y == dest.y) {
		return true;
	}
	return false;
}

double aStar::calculateH(int x, int y, node dest)
{
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}

list<node> aStar::aStarAlg(node player, node dest, map p_m) 
{
	list<node> empty;
	if (isValid(dest) == false) {
		cout << "Destination is an obstacle" << endl;
		return empty;
		//Destination is invalid
	}
	if (isDestination(player.x, player.y, dest)) {
		cout << "You are the destination" << endl;
		return empty;
		//You clicked on yourself
	}
	bool closedList[map::x][map::y];

	//Initialize whole map
	//array<array<node, (map::x)>, (map::y)> allMap;
	map allMap = p_m;
	//node allMap[map::x][map::y];

	for (int x = 0; x < map::x; x++) {
		for (int y = 0; y < map::y; y++) {
			allMap.tiles[x][y].fCost = FLT_MAX;
			allMap.tiles[x][y].gCost = FLT_MAX;
			allMap.tiles[x][y].hCost = FLT_MAX;
			allMap.tiles[x][y].parentX = -1;
			allMap.tiles[x][y].parentY = -1;
			allMap.tiles[x][y].x = x;
			allMap.tiles[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	//Initialize our starting list
	int x = player.x;
	int y = player.y;
	allMap.tiles[x][y].fCost = 0.0;
	allMap.tiles[x][y].gCost = 0.0;
	allMap.tiles[x][y].hCost = 0.0;
	allMap.tiles[x][y].parentX = x;
	allMap.tiles[x][y].parentY = y;

	vector<node> openList;
	openList.emplace_back(allMap.tiles[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < map::x * map::y) {
		node v_node;
		do {
			//This do-while loop could be replaced with extracting the first
			//element from a set, but you'd have to make the openList a set.
			//To be completely honest, I don't remember the reason why I do
			//it with a vector, but for now it's still an option, although
			//not as good as a set performance wise.
			float temp = FLT_MAX;
			vector<node>::iterator itNode;
			for (vector<node>::iterator it = openList.begin();
				it != openList.end(); it = next(it)) {
				node n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					itNode = it;
				}
			}
			v_node = *itNode;
			openList.erase(itNode);
		} while (isValid(v_node) == false);

		x = v_node.x;
		y = v_node.y;
		closedList[x][y] = true;

		//For each neighbour starting from North-West to South-East
		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (isValid(node(x + newX, y + newY))) {
					if (isDestination(x + newX, y + newY, dest))
					{
						//Destination found - make path
						allMap.tiles[x + newX][y + newY].parentX = x;
						allMap.tiles[x + newX][y + newY].parentY = y;
						destinationFound = true;
						return makePath(allMap.tiles, dest);
					}
					else if (closedList[x + newX][y + newY] == false)
					{
						gNew = v_node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;
						// Check if this path is better than the one already present
						if (allMap.tiles[x + newX][y + newY].fCost == FLT_MAX ||
							allMap.tiles[x + newX][y + newY].fCost > fNew)
						{
							// Update the details of this neighbour node
							allMap.tiles[x + newX][y + newY].fCost = fNew;
							allMap.tiles[x + newX][y + newY].gCost = gNew;
							allMap.tiles[x + newX][y + newY].hCost = hNew;
							allMap.tiles[x + newX][y + newY].parentX = x;
							allMap.tiles[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap.tiles[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (destinationFound == false) {
		cout << "Destination not found" << endl;
		return empty;
	}
}

//list<node> aStar::makePath(array<array<node, (map::x)>, (map::y)> map, node dest)
list<node> aStar::makePath(node map[][50], node dest)
{
	try {
		cout << "Found a path" << endl;
		int x = dest.x;
		int y = dest.y;
		stack<node> path;
		list<node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			&& map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;

		}
		path.push(map[x][y]);

		while (!path.empty()) {
			node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		return usablePath;
	}
	catch (const exception & e) {
		cout << e.what() << endl;
	}
}

#pragma once
#include "node.h"
#include <list>
#include <vector>
#include <array>
#include <stack>
#include <iostream>
#include "map.h"

using namespace std;

class aStar
{
	public:
		aStar();

		static bool isValid(int x, int y);
		static bool isValid(node p_node);
		static bool isDestination(int x, int y, node dest);
		static double calculateH(int x, int y, node dest);
		static list<node> aStarAlg(node player, node dest, map p_m);
		//static list<node> makePath(array<array<node, (map::x)>, (map::y)> map, node dest);
		static list<node> makePath(node map[][50], node dest);
};


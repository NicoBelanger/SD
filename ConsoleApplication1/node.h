#pragma once
class node
{
	public:
		int y;
		int x;
		int parentX;
		int parentY;
		float gCost;
		float hCost;
		float fCost;
		bool obstacle;

		node();
		node(int p_x, int p_y);

		friend bool operator < (const node& lhs, const node& rhs);
};


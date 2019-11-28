#pragma once
#include <iostream>
#include "arpRow.h"
#include <list>

using namespace std;

class arpTable
{
	list<arpRow> table;

public:
	void insertArp(arpRow p_row);
	arpRow lookup(ip p_ip);
};


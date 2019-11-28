#include "arpTable.h"


void arpTable::insertArp(arpRow p_row)
{
	table.push_back(p_row);
}

arpRow arpTable::lookup(ip p_ip)
{
	list<arpRow>::iterator it;

	for (it = table.begin(); it != table.end(); ++it) {

		if (it->ipAdd->ipadress == p_ip.ipadress)
		{
			return *it;
		}
	}

	return arpRow();
}

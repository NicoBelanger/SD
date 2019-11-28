#include "arpRow.h"

arpRow::arpRow()
{
	ipAdd = NULL;
	device = NULL;
	nullRow = true;
}

arpRow::arpRow(ip* p_ip, net_device* p_device)
{
	ipAdd = p_ip;
	device = p_device;
	nullRow = false;
}

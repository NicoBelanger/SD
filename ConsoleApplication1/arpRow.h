#pragma once
class net_device;
#include "ip.h"

class arpRow
{
	public:
		ip* ipAdd;
		net_device* device;
		bool nullRow;

		arpRow();
		arpRow(ip* p_ip, net_device* p_device);
};


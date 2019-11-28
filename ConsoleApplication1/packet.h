#pragma once
#include "ip.h"

class packet
{
	public:
		ip source;
		ip destination;
		string data;

	public:
		packet();
		packet(ip p_source, ip p_destination, string p_data);
};


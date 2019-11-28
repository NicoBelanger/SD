#pragma once
#include "net_device.h"
#include "router.h"
#include "arpTable.h"

class subnet
{
	public:
		list<net_device*> devices;
		arpTable arp_table;
		router* gateway;

	public:
		subnet();
		void setGateway(router* p_rout);
};


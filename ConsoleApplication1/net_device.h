#pragma once
#include "position.h"
#include "packet.h"
#include "arpTable.h"
#include <iostream>
#include <list>
#include "node.h"
#include "tools.h"

using namespace std;

class net_device : public node
{
	public:
		string name;
		ip ipAdd;
		arpTable *arp_table;

	public: 
		net_device();
		net_device(string p_name, int x, int y, ip p_ip, arpTable *p_arp);
		virtual void receivePacket(packet p_packet)=0;
		virtual void sendPacket(ip p_dest, string p_data)=0;
};


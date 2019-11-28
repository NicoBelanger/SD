#include <string.h>
#include <string>
#include <list>
#include "position.h"
#include "ip.h"
#include "packet.h"
#include "arpTable.h"
#include "router.h"

using namespace std;

#pragma once
class thing : public net_device
{
	public:
		router* gateway;
		int port_forw;

		thing(string p_name, int x, int y, ip p_ip, arpTable* p_arp, router* p_gateway, int p_portForw);
		void sendPacket(ip p_dest, string p_data) override;
		void receivePacket(packet p_packetreceived) override;
};


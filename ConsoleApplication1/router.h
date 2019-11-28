#pragma once
#include "ip.h"
#include "position.h"
#include "net_device.h"
#include "packet.h"
#include "node.h"
#include "tools.h"

class router : public net_device
{
	public:
		struct patRow 
		{
			ip privateIP;
			int associatedPort;
		};

		ip publicIp;
		int range;
		list<packet> packet_buffer;
		list<patRow> patTable;
		int portCpt;

	public:
		router();
		router(string p_name, int x, int y, ip p_ip, arpTable* p_arp, ip p_publicIP, int p_range);
		void routeOutsideLocal(packet p_packet);
		patRow PATresolver(ip p_ip);
		string PATlookup(int p_port);
		void packetFromDrone(packet m_pac);
		void insertPATtable(string p_privIP, int p_port);
		void sendPacket(ip p_dest, string p_data) override;
		void receivePacket(packet p_packetreceived) override;
};


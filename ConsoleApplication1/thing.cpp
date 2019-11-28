#include "thing.h"

thing::thing(string p_name, int x, int y, ip p_ip, arpTable* p_arp, router* p_gateway, int p_portForw) :
	net_device(p_name, x, y, p_ip, p_arp)
{
	gateway = p_gateway;
	port_forw = p_portForw;
}

void thing::sendPacket(ip p_dest, string p_data)
{
	packet packet2send = packet(ipAdd, p_dest, p_data);
	bool nullRow = ((*arp_table).lookup(p_dest)).nullRow;
	
	if(!nullRow)
	{
		net_device* where2send = ((*arp_table).lookup(p_dest)).device;
		std::cout << name + " a envoye un packet vers " + (*where2send).name << endl;
		(*where2send).receivePacket(packet2send);
	}
	else 
	{
		cout << "Adresse " << p_dest.ipadress << " n est pas dans le subnet. Envoie du packet au router" << endl;
		(*gateway).routeOutsideLocal(packet2send);
	}
	
}

void thing::receivePacket(packet p_packetreceived)
{
	if (p_packetreceived.destination.ipadress == ipAdd.ipadress)
	{
		std::cout << name + " a recu un packet contenant le message: " + p_packetreceived.data << endl << endl;
		if (p_packetreceived.data != "ACK")
			sendPacket(p_packetreceived.source.ipadress, "ACK");
	}
}


#include "router.h"

router::router()
{
}

router::router(string p_name, int x, int y, ip p_ip, arpTable* p_arp, ip p_publicIP, int p_range):
	net_device(p_name, x, y, p_ip, p_arp)
{
	publicIp = p_publicIP;
	range = p_range;
	portCpt = 0;
}

void router::routeOutsideLocal(packet p_packet)
{
	patRow pr = PATresolver(p_packet.source);

	string publicIPwithPort = publicIp.ipadress + ":" + to_string(pr.associatedPort);

	p_packet.source = ip(publicIPwithPort);

	packet_buffer.push_back(p_packet);

	std::cout << "Le packet Source: " << p_packet.source.ipadress << " Destination: " << p_packet.destination.ipadress  
		<< " a ete ajoute au buffer du router" << endl << endl;
}

router::patRow router::PATresolver(ip p_ip)
{
	patRow pr;

	list<patRow>::iterator it;

	for (it = patTable.begin(); it != patTable.end(); ++it) {

		if (it->privateIP.ipadress == p_ip.ipadress)
		{
			return *it;
		}
	}

	/*portCpt++;
	pr.associatedPort = portCpt;
	pr.privateIP = p_ip;
	patTable.push_back(pr);

	return pr;*/
}

string router::PATlookup(int p_port)
{
	patRow pr;

	list<patRow>::iterator it;

	for (it = patTable.begin(); it != patTable.end(); ++it) {

		if (it->associatedPort == p_port)
		{
			return it->privateIP.ipadress;
		}
	}

	return "Not Found";
}

void router::packetFromDrone(packet m_pac)
{
	int port = tools::string2int(tools::split(m_pac.destination.ipadress, ':')[1]);
	string privateIP = PATlookup(port);

	bool nullRow = ((*arp_table).lookup(privateIP)).nullRow;

	if (!nullRow)
	{
		net_device* where2send = ((*arp_table).lookup(privateIP)).device;
		m_pac.destination.ipadress = (*where2send).ipAdd.ipadress;
		(*where2send).receivePacket(m_pac);
	}

	//cout << m_pac.data << endl;
}

void router::insertPATtable(string p_privIP, int p_port)
{
	patRow pr;

	pr.privateIP = p_privIP;
	pr.associatedPort = p_port;

	patTable.push_back(pr);
}

void router::sendPacket(ip p_dest, string p_data)
{
	/*packet packet2send = packet(ipAdd, p_dest, p_data);

	net_device where2send = *((*arp_table).lookup(p_dest)).device;
	std::cout << name + " a envoye un packet vers " + where2send.name << endl;

	where2send.receivePacket(packet2send);*/
	packet packet2send = packet(ipAdd, p_dest, p_data);
	bool nullRow = ((*arp_table).lookup(p_dest)).nullRow;

	if (!nullRow)
	{
		net_device* where2send = ((*arp_table).lookup(p_dest)).device;



		std::cout << name + " a envoye un packet vers " + (*where2send).name << endl;
		(*where2send).receivePacket(packet2send);
	}
}

void router::receivePacket(packet p_packetreceived)
{
	if (p_packetreceived.destination.ipadress == ipAdd.ipadress)
	{
		std::cout << name + " a recu un packet contenant le message: " + p_packetreceived.data << endl << endl;
		if (p_packetreceived.data != "ACK")
			sendPacket(p_packetreceived.source.ipadress, "ACK");
	}
}

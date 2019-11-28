#include "drone.h"
#include "aStar.h"

drone::drone():node()
{
}

drone::drone(int x, int y, map* p_m) :
	node(x, y)
{
	m = p_m;
}

void drone::sendRequestToRouter(router* p_rou)
{
	list<packet>::iterator it;

	for (it = p_rou->packet_buffer.begin(); it != p_rou->packet_buffer.end(); ++it)
	{
		pacList pl;
		pl.pac = (*it);
		pl.canDelete = false;
		packetBuff.push_back(pl);
	}

	p_rou->packet_buffer.clear();
}

void drone::addToRouterPosTable(string p_pubIP, router* p_rou)
{
	routerPosRow rpr;
	rpr.publicIP = p_pubIP;
	rpr.rou = p_rou;

	routerPosTables.push_back(rpr);
}

void drone::moveToRouter(router* p_rou, map* p_m)
{
	for (node p_node : aStar::aStarAlg(*this, *p_rou, *p_m))
	{
		x = p_node.x;
		y = p_node.y;
		cout << "(" << x << ", " << y << ")" << endl;
	}

	cout << endl;
}

void drone::deliverBuffer()
{
	packet pac = packetBuff.front().pac;

	string ipWithoutPort = tools::split(pac.destination.ipadress, ':')[0];

	router* rout = tableLookup(ipWithoutPort);
	moveToRouter(rout, m);

	list<pacList>::iterator it;

	for (it = packetBuff.begin(); it != packetBuff.end(); ++it) 
	{
		ipWithoutPort = tools::split((*it).pac.destination.ipadress, ':')[0];

		if (ipWithoutPort == (*rout).publicIp.ipadress)
		{
			rout->packetFromDrone((*it).pac);
			(*it).canDelete = true;
		}
	}

	packetBuff.remove_if([](pacList i) { return i.canDelete == true; });
}

router* drone::tableLookup(ip p_ip)
{
	list<routerPosRow>::iterator it;

	for (it = routerPosTables.begin(); it != routerPosTables.end(); ++it) {

		if ((*it).publicIP.ipadress == p_ip.ipadress)
		{
			return (*it).rou;
		}
	}

	return nullptr;
}

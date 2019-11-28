#include <iostream>
#include "subnet.h"
#include "thing.h"
#include "drone.h"
#include "aStar.h"

using namespace std;

int main()
{
	map m = map();
	drone drone1 = drone(0, 0, &m);

	m.createObstacle(12, 12, 25, 25);

	subnet sub1 = subnet();
	router rou1 = router("Router1", 12, 0, ip("192.168.1.0"), &sub1.arp_table, ip("10.0.0.0"), 1);
	sub1.setGateway(&rou1);
	m.setTile(rou1);
	drone1.addToRouterPosTable(rou1.publicIp.ipadress, &rou1);

	thing pc1 = thing("PC1", 12, 1, ip("192.168.1.1"), &sub1.arp_table, sub1.gateway, 80);
	thing pc2 = thing("PC2", 13, 1, ip("192.168.1.2"), &sub1.arp_table, sub1.gateway, 1234);
	thing pc3 = thing("PC3", 11, 1, ip("192.168.1.3"), &sub1.arp_table, sub1.gateway, 2020);
	m.setTile(pc1);
	m.setTile(pc2);
	m.setTile(pc3);

	rou1.insertPATtable(pc1.ipAdd.ipadress, pc1.port_forw);
	rou1.insertPATtable(pc2.ipAdd.ipadress, pc2.port_forw);
	rou1.insertPATtable(pc3.ipAdd.ipadress, pc3.port_forw);

	sub1.arp_table.insertArp(arpRow(&rou1.ipAdd, &rou1));
	sub1.arp_table.insertArp(arpRow(&pc1.ipAdd, &pc1));
	sub1.arp_table.insertArp(arpRow(&pc2.ipAdd, &pc2));
	sub1.arp_table.insertArp(arpRow(&pc3.ipAdd, &pc3));

	subnet sub2 = subnet();
	router rou2 = router("Router2", 12, 49, ip("192.168.1.0"), &sub2.arp_table, ip("10.1.1.1"), 1);
	sub2.setGateway(&rou2);
	drone1.addToRouterPosTable(rou2.publicIp.ipadress, &rou2);

	thing pc4 = thing("PC4", 12, 48, ip("192.168.1.1"), &sub2.arp_table, sub2.gateway, 80);
	m.setTile(pc4);

	rou2.insertPATtable(pc4.ipAdd.ipadress, pc4.port_forw);

	sub2.arp_table.insertArp(arpRow(&rou2.ipAdd, &rou2));
	sub2.arp_table.insertArp(arpRow(&pc4.ipAdd, &pc4));

	pc1.sendPacket(pc2.ipAdd, "Salut, ca va?");
	pc3.sendPacket(ip("10.1.1.1:80"), "Voici un test");
	pc3.sendPacket(ip("10.1.1.1:80"), "Un autre test");

	drone1.moveToRouter(&rou1, &m);
	drone1.sendRequestToRouter(&rou1);

	drone1.deliverBuffer();
}
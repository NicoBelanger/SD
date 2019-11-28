#include "net_device.h"

net_device::net_device()
{
}

net_device::net_device(string p_name, int x, int y, ip p_ip, arpTable* p_arp):
	node(x,y)
{
	name = p_name;
	ipAdd = p_ip;
	arp_table = p_arp;
	obstacle = false;
}

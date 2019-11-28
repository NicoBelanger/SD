#include "packet.h"

packet::packet()
{}

packet::packet(ip p_source, ip p_destination, string p_data)
{
	source = p_source;
	destination = p_destination;
	data = p_data;
}
